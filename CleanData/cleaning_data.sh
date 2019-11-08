#!/bin/bash

#List of all the data files that we will use in this project
declare -a data=(smhi-opendata_Lulea.csv smhi-opendata_Lund.csv smhi-opendata_Visby.csv smhi-opendata_Umea.csv smhi-opendata_Falsterbo.csv smhi-opendata_Soderarm.csv smhi-openda_Karlstad.csv smhi-opendata_Boras.csv smhi-opendata_Falun.csv)


#test list
#declare -a data=(smhi-opendata_Lulea.csv)



cd datasets/

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

	#Put top 9 lines, containing all of the information about the data
	head -n 9 ${name} >> ${name::-4}/info_${name::-3}txt

	#for each line in cvs
	while IFS=, read -r field1 
	do
	#clean lines that contain text after the data 
	if [[ $field1 == *";;"* ]]; then
		if [[ $field1 == *"G;;"* ]]; then
		echo -n "$field1"|sed 's/;;.*//' >> ${name::-4}/data_${name::-3}txt
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
	
	
	#find the temperture each day 
	touch ${name::-4}/data_temp_day_${name::-3}txt

	while IFS= read -r line
	do
	grep ${line} ${name::-4}/data_${name::-3}txt | cut -d ';' -f 3- | tr -d ';G\n'  >> ${name::-4}/data_temp_day_${name::-3}txt
	echo "\n" >> ${name::-4}/data_temp_day_${name::-3}txt
	
	done < ${name::-4}/data_date_${name::-3}txt

	
done
cd ..
echo "done"
