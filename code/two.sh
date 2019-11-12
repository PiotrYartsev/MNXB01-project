#!/bin/bash

#List of all the data files that we will use in this project
#declare -a data=(smhi-opendata_Lulea.csv smhi-opendata_Lund.csv smhi-opendata_Visby.csv smhi-opendata_Umea.csv smhi-opendata_Falsterbo.csv smhi-opendata_Soderarm.csv smhi-openda_Karlstad.csv smhi-opendata_Boras.csv smhi-opendata_Falun.csv)

#test list
declare -a data=(smhi-opendata_Lulea.csv )

cd .. 

for name in "${data[@]}"
do
#remove files if they already exist
if [ -f CleanData/datasets/${name::-4}/data_years_${name::-3}txt ]; then
	   rm -f CleanData/datasets/${name::-4}/data_years_${name::-3}txt
	   echo "Deleted CleanData/datasets/${name::-4}/data_years_${name::-3}txt"
fi	
	
if [ -f CleanData/datasets/${name::-4}/day_temp_med.txt ]; then
	   rm -f CleanData/datasets/${name::-4}/day_temp_med.txt
	   echo "Deleted CleanData/datasets/${name::-4}/day_temp_med.txt"
fi

if [ -f CleanData/datasets/${name::-4}/day_temp_med_day.txt ]; then
	   rm -f CleanData/datasets/${name::-4}/day_temp_med_day.txt
	   echo "Deleted CleanData/datasets/${name::-4}/day_temp_med_day.txt"
fi

if [ -f CleanData/datasets/${name::-4}/day_temp_med_year.txt ]; then
	   rm -f CleanData/datasets/${name::-4}/day_temp_med_year.txt
	   echo "Deleted CleanData/datasets/${name::-4}/day_temp_med_year.txt"
fi

if [ -f CleanData/datasets/${name::-4}/Final.txt ]; then
	   rm -f CleanData/datasets/${name::-4}/Final.txt
	   echo "Deleted CleanData/datasets/${name::-4}/Final.txt"
fi	

if [ -f CleanData/datasets/${name::-4}/Final_final.txt ]; then
	   rm -f CleanData/datasets/${name::-4}/Final_final.txt
	   echo "Deleted CleanData/datasets/${name::-4}/Final_final.txt"
fi	


echo "Runing c++ code to calculate daily average temperature"
#use c++ code that does calculates the average temp each day

	if [ -f input.txt ]; then
	   rm -r input.txt
	fi
		if [ -f CleanData/datasetsday_temp_med.txt ]; then
	   rm -r CleanData/datasetsday_temp_med.txt
	fi
	sed -i s/\\n\"//g CleanData/datasets/${name::-4}/data_temp_day_${name::-3}txt 
	touch input.txt
	echo CleanData/datasets/${name::-4}/data_temp_day_${name::-3}txt >> input.txt
	g++ code/average_day_temp.cpp -o a.out
	./a.out < input.txt > CleanData/datasets/${name::-4}/day_temp_med.txt
	rm input.txt
echo "Done running the c++ code"


#compere if number of days match number of temperatures 
if [ "$(wc -l < CleanData/datasets/${name::-4}/day_temp_med.txt)" -gt "$(wc -l < CleanData/datasets/${name::-4}/data_temp_day_${name::-3}txt)" ];then
	echo -e "Days and daily temp don't match, everything is on fire"
	echo -e "$(wc -l < CleanData/datasets/${name::-4}/day_temp_med.txt)"
	echo -e "$(wc -l < CleanData/datasets/${name::-4}/data_temp_day_${name::-3}txt)"
	exit 1
	fi

echo "Extracting data to get txt with all average temperatures each day each year"
#make a list of years
while IFS= read -r line
	do
	echo ${line:0:4} >> CleanData/datasets/${name::-4}/data_years_${name::-3}txt
done < CleanData/datasets/${name::-4}/data_date_${name::-3}txt

# Add dates to daily average
paste CleanData/datasets/${name::-4}/day_temp_med.txt CleanData/datasets/${name::-4}/data_date_${name::-3}txt > CleanData/datasets/${name::-4}/day_temp_med_day.txt
echo " \n" >> CleanData/datasets/${name::-4}/day_temp_med_day.txt

touch CleanData/datasets/${name::-4}/day_temp_med_year.txt
chmod 777 CleanData/datasets/${name::-4}/day_temp_med_year.txt

#removes duplicate dates from ${name::-4}/data_date_${name::-3}txt
sed -i '$!N; /^\(.*\)\n\1$/!P; D' CleanData/datasets/${name::-4}/data_years_${name::-3}txt

#add date infront of each temperature 
while IFS= read -r line
	do
	echo -e "${line} " >> CleanData/datasets/${name::-4}/day_temp_med_year.txt
grep $line CleanData/datasets/${name::-4}/day_temp_med_day.txt | while read -r linetwo ; do
	
	truncate --size -1 CleanData/datasets/${name::-4}/day_temp_med_year.txt
	echo -e $linetwo | cut -d ' ' -f 1 >> CleanData/datasets/${name::-4}/day_temp_med_year.txt
done
done < CleanData/datasets/${name::-4}/data_years_${name::-3}txt
echo "Done extracting data"

echo "Count the nummber of days that have average temperature bellow zero each year"
#count the number of instances for each year where the daily average temperature was below 0
while IFS= read -r line
	do
echo $line | grep -o "-" | wc -l >> CleanData/datasets/${name::-4}/Final.txt
done < CleanData/datasets/${name::-4}/day_temp_med_year.txt

#remove values zero 
echo "remove lines that are less 5"
echo CleanData/datasets/${name::-4}/Final.txt grep -r "0\n" . | wc -l

sed -i 1,10d  CleanData/datasets/${name::-4}/Final.txt
sed -i 1,10d  CleanData/datasets/${name::-4}/data_years_${name::-3}txt
sed -i '$d' CleanData/datasets/${name::-4}/Final.txt
sed -i '$d' CleanData/datasets/${name::-4}/data_years_${name::-3}txt
done

echo "Plot the data for Lulea"
cd CleanData/
echo "$(readlink -f datasets/${name::-4}/data_years_${name::-3}txt) \n"
echo "$(realpath datasets/${name::-4}/data_years_${name::-3}txt)" >> input.txt
echo "$(realpath datasets/${name::-4}/Final.txt)" >> input.txt
echo "$(readlink -f datasets/${name::-4}/Final.txt) \n"
cd ..
echo "$(readlink -f code)" >> input.txt
echo "$(readlink -f code) \n" 
cd CleanData/
if [ -f Lulea.pdf ]; then
	   rm -f Lulea.pdf
	   echo "Deleted Lulea.pdf"
fi	
root .x graph.C+ < input.txt
.q
echo "done"
