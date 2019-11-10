#!/bin/bash

#List of all the data files that we will use in this project
#declare -a data=(smhi-opendata_Lulea.csv smhi-opendata_Lund.csv smhi-opendata_Visby.csv smhi-opendata_Umea.csv smhi-opendata_Falsterbo.csv smhi-opendata_Soderarm.csv smhi-openda_Karlstad.csv smhi-opendata_Boras.csv smhi-opendata_Falun.csv)



#test list
declare -a data=(smhi-opendata_Lulea.csv )


cd datasets/

for name in "${data[@]}"
	do
	
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

#use c++ code that does stuff
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

while IFS= read -r line
	do
	echo -e "${line} " >> ${name::-4}/day_temp_med_year.txt
grep $line ${name::-4}/day_temp_med_day.txt | while read -r linetwo ; do
	
	truncate --size -1 ${name::-4}/day_temp_med_year.txt
	echo -e $linetwo | cut -d ' ' -f 1 >> ${name::-4}/day_temp_med_year.txt
done
done < ${name::-4}/data_years_${name::-3}txt
	

while IFS= read -r line
	do
echo $line | grep -o "-" | wc -l >> ${name::-4}/Final.txt
done < ${name::-4}/day_temp_med_year.txt



#sed -i '1d;10d' ${name::-4}/Final.txt 
#sed -i '1d;10d' ${name::-4}/data_years_${name::-3}txt
done
cd ..



root .x graph.C
.q
echo "done"
