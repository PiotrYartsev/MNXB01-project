#!/bin/bash

#List of all the data files that we will use in this project
#declare -a data=(smhi-opendata_Lulea.csv smhi-opendata_Lund.csv smhi-opendata_Visby.csv smhi-opendata_Umea.csv smhi-opendata_Falsterbo.csv smhi-opendata_Soderarm.csv smhi-openda_Karlstad.csv smhi-opendata_Boras.csv smhi-opendata_Falun.csv)


#test list
declare -a data=(smhi-opendata_Lulea.csv )


cd Cleandata/datasets/

for name in "${data[@]}"
	do
	echo "new city"
	#if directory already exist for a data file remove it
	if [ -d ${name::-4} ]; then
	   rm -r ${name::-4}
	   echo "Direcetory ${name::-4} already exist, removing it and repalcing with new ${name::-4} directory"
	fi
	#create a directory for each data file to store the output
	mkdir ${name::-4}
	#create a textfile for storing cleaned data
	touch ${name::-4}/data_${name::-3}txt
	#create a textfile for storing information about the data
	touch ${name::-4}/info_${name::-3}txt

	#for each line in cvs
	while IFS=, read -r field1 
	do
	#clean lines that contain text after the data 
	if [[ $field1 == *";;"* ]]; then
		if [[ $field1 == *"G;;"* ]]; then
		echo -n "$field1"|sed 's/;;.*//' >> "${name::-4}/data_${name::-3}txt"
		else
		continue
		fi
	fi 

	#add data from cvs to file named data_"name".txt
	if [[ $field1 == *"G"* ]]; then
	  echo -n -e "$field1 \n" >> ${name::-4}/data_${name::-3}txt
	fi 
	done < ${name}
	
	
	touch ${name::-4}/data_date_${name::-3}txt
	#extract date, time and temp from cvs
	touch ${name::-4}/data_temp_${name::-3}txt
	while IFS=';' read -r one two three four
	do
	  echo -n -e "$one\n"  >> ${name::-4}/data_date_${name::-3}txt
	  echo -n -e "$two\n"  >> ${name::-4}/data_time_${name::-3}txt
	  echo -n -e "$three\n"  >> ${name::-4}/data_temp_${name::-3}txt
	done < ${name::-4}/data_${name::-3}txt
	
	
	#removes duplicate dates from ${name::-4}/data_date_${name::-3}txt
	sed -i -n '$!N; /^\(.*\)\n\1$/!P; D' ${name::-4}/data_date_${name::-3}txt
	
	#find the temperture measurment each day 
	touch ${name::-4}/data_temp_day_${name::-3}txt

	while IFS= read -r line
	do
	grep ${line} ${name::-4}/data_${name::-3}txt | cut -d ';' -f 3- | tr -d 'G\n'  >> ${name::-4}/data_temp_day_${name::-3}txt
	echo " \n" >> ${name::-4}/data_temp_day_${name::-3}txt
	done < ${name::-4}/data_date_${name::-3}txt
	

	#compare leangth of file with dates with daily temperture
	if [ "$(wc -l < ${name::-4}/data_temp_day_${name::-3}txt)" -gt "$(wc -l < ${name::-4}/data_date_${name::-3}txt)" ];then
	echo -e "Days and daily temp don't match, everything is on fire"
	echo -e "$(wc -l < ${name::-4}/data_temp_day_${name::-3}txt)"
	echo -e "$(wc -l < ${name::-4}/data_date_${name::-3}txt)"
	exit 1
	fi
	echo "test"

#remove files if they already exist
if [ -f ${name::-4}/data_years_${name::-3}txt ]; then
	   rm -f ${name::-4}/data_years_${name::-3}txt
	   echo "Deleted ${name::-4}/data_years_${name::-3}txt"
fi	
	
if [ -f ${name::-4}/day_temp_med.txt ]; then
	   rm -f ${name::-4}/day_temp_med.txt
	   echo "Deleted ${name::-4}/day_temp_med.txt"
fi

if [ -f ${name::-4}/day_temp_med_day.txt ]; then
	   rm -f ${name::-4}/day_temp_med_day.txt
	   echo "Deleted ${name::-4}/day_temp_med_day.txt"
fi

if [ -f ${name::-4}/day_temp_med_year.txt ]; then
	   rm -f ${name::-4}/day_temp_med_year.txt
	   echo "Deleted ${name::-4}/day_temp_med_year.txt"
fi

if [ -f ${name::-4}/Final.txt ]; then
	   rm -f ${name::-4}/Final.txt
	   echo "Deleted ${name::-4}/Final.txt"
fi	

if [ -f ${name::-4}/Final_final.txt ]; then
	   rm -f ${name::-4}/Final_final.txt
	   echo "Deleted ${name::-4}/Final_final.txt"
fi	

#use c++ code that does calculates the average temp each day
	cd ..
	if [ -f input.txt ]; then
	   rm -r input txt
	fi
		if [ -f day_temp_med.txt ]; then
	   rm -r day_temp_med.txt
	fi
	sed -i s/\\n\"//g ${name::-4}/data_temp_day_${name::-3}txt 
	touch input.txt
	echo datasets/${name::-4}/data_temp_day_${name::-3}txt >> input.txt
	g++ average_day_temp.cpp -o a.out
	./a.out < input.txt > datasets/${name::-4}/day_temp_med.txt
	rm input.txt
	cd datasets/

#compere if number of days match number of temperatures 
if [ "$(wc -l < ${name::-4}/day_temp_med.txt)" -gt "$(wc -l < ${name::-4}/data_temp_day_${name::-3}txt)" ];then
	echo -e "Days and daily temp don't match, everything is on fire"
	echo -e "$(wc -l < ${name::-4}/day_temp_med.txt)"
	echo -e "$(wc -l < ${name::-4}/data_temp_day_${name::-3}txt)"
	exit 1
	fi



#make a list of years
while IFS= read -r line
	do
	echo ${line:0:4} >> ${name::-4}/data_years_${name::-3}txt
done < ${name::-4}/data_date_${name::-3}txt

# Add dates to daily average
paste ${name::-4}/day_temp_med.txt ${name::-4}/data_date_${name::-3}txt > ${name::-4}/day_temp_med_day.txt
echo " \n" >> ${name::-4}/day_temp_med_day.txt

touch ${name::-4}/day_temp_med_year.txt
chmod 777 ${name::-4}/day_temp_med_year.txt
echo "start"

#removes duplicate dates from ${name::-4}/data_date_${name::-3}txt
sed -i '$!N; /^\(.*\)\n\1$/!P; D' ${name::-4}/data_years_${name::-3}txt

#add date infront of each temperature 
while IFS= read -r line
	do
	echo -e "${line} " >> ${name::-4}/day_temp_med_year.txt
grep $line ${name::-4}/day_temp_med_day.txt | while read -r linetwo ; do
	
	truncate --size -1 ${name::-4}/day_temp_med_year.txt
	echo -e $linetwo | cut -d ' ' -f 1 >> ${name::-4}/day_temp_med_year.txt
done
done < ${name::-4}/data_years_${name::-3}txt
	
#count the number of instances for each year where the daily average temperature was below 0
while IFS= read -r line
	do
echo $line | grep -o "-" | wc -l >> ${name::-4}/Final.txt
done < ${name::-4}/day_temp_med_year.txt


done
cd ..


root .x graph.C
.q
echo "done"
