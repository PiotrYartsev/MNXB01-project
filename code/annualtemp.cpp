
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
/*This script contains two functions, yearly_average: Takes an input file, and creates an output with the year and the mean temperature that year separated by space. 
 * and the function output_annual_temp that outputs the result for all the years in the data set.
 * 
 * Check the format of the Uppsala file. If you want to change the column to average, just change temp_col, and the number_of_columns, if applied to another dataset.
 * NOTE: It only works in the format year something temperature something, not with dates (1977 is ok but 1972-07-01 is not) or columns separated by commas.*/
	
double yearly_average(
int chosen_year, int number_of_columns, int temp_col){
	//Choose path to file
	std::ifstream inFile("../CleanData/datasets/uppsala_tm_1722-2013.dat");
	if(!inFile) {
		std::cout << "Not in file";
		return 1;
		}
		
	double num = 0.;
	int year = 0;
	int n = 0;
	int remainder = 0;
	int index = 0;
	double temp_sum = 0;
	double average = 0;
	
	while(inFile >> num) {
	
	remainder = int(n % number_of_columns);
	if((year == chosen_year) && (remainder == temp_col)) {
		temp_sum += num;
		}
	if(remainder == 0) {
	year = int(num);
	
	if(year == chosen_year)
	{
	index++;
	}

	if(year > chosen_year) {
	break;}
	}
	n++;
	}

	if (index != 0) {
		average = temp_sum/index;
	return average;
	} else {
	cout << "Year not in data set!" << endl;
	return 1;}
}

int output_annual_temp(int first_year, int last_year) {
	cout << "Preprocessing data set, this might take a while... Drink some coffee." << endl;
	int y = first_year;
	ofstream outFile("../ProcessedData/UppsalaData/annualtemp.txt");
	if(!outFile) {
		std::cout << "Error" << endl;
		return 1;
		}
	while(y <= last_year) {
		outFile << y << " " << setprecision(2) << yearly_average(y, 6, 4) << endl;
		y++;
	}
	outFile.close();
	return 0;	
}


