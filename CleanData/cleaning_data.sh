#!/bin/bash

# this function prints an error with the information on how to run this
# script.
usage(){
	echo "----"
	echo -e "  Wrong syntax. To call this script please use"
	echo -e "   $0 '<artistlastname>_<artistname>' ['<artistlastname>_<artistname>' ...]"
	echo -e "  Example:"
	echo -e "   $0 'Hubbard_Rob'"
	echo "----"
}



####### CODE START #####################################################



#List of all the data files that we will use in this project
#declare -a data=(smhi-opendata_Lulea.csv smhi-opendata_Lund.csv smhi-opendata_Visby.csv smhi-opendata_Umea.csv smhi-opendata_Falsterbo.csv smhi-opendata_Soderarm.csv smhi-openda_Karlstad.csv smhi-opendata_Boras.csv smhi-opendata_Falun.csv)


#test list
declare -a data=(smhi-opendata_Lulea.csv)



echo "${data[0]}"
#Check that all those files exist in the folder data.
#cd datasets/
#for n in ${data}
#do
#	if [ ! -e  ${data[n]} ];then
#	echo -e "File ${n} is missing"
#	exit 1
#	fi
#done
#cd ..
#STATSDIR="stats"

#if [ -d "stats" ]; then
#  rm -r stats
#   echo "Direcetory stats already exist, removing it and repalcing with new stats directory"
#fi

cd datasets/

for name in ${data}
do

if [ -d ${name::-4} ]; then
   rm -r ${name::-4}
   echo "Direcetory ${name::-4} already exist, removing it and repalcing with new ${name::-4} directory"
fi

mkdir ${name::-4}
touch ${name::-4}/data_${name::-3}txt
touch ${name::-4}/info_${name::-3}txt


echo $(sed -n "1p" "$name") >> ${name::-4}/info_${name::-3}txt
while IFS=, read -r field1 
do
if [[ $field1 == *";;"* ]]; then
	continue
fi 


if [[ $field1 == *"G"* ]]; then
  echo -n "$field1" >> ${name::-4}/data_${name::-3}txt
fi 
 
done < ${name}
done
cd ..
echo "done"

#if [[ ( $? != 0 ) || (! -e $STATSDIR) ]]; then
#   echo "Directory creation failed or stats directory missing. Please check your code."
#   echo "The script cannot continue. Exiting..."
#   exit 1
#fi
