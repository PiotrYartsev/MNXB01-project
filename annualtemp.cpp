
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
/*This script takes an input file, and creates an output with the year and the mean temperature that year separated by space.
 * Check the format of the Uppsala file. If you want to change the column to average, just change temp_col, and the number_of_columns, if applied to another dataset.
 * NOTE: It only works in the format year something temperature something, not with dates (1977 is ok but 1972-07-01 is not) or columns separated by commas.*/
	
double yearly_average(
int chosen_year, int number_of_columns, int temp_col){
	//Choose path to file
	std::ifstream inFile("CleanData/datasets/uppsala_tm_1722-2013.dat");
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
	int y = first_year;
	ofstream outFile("CleanData/UppsalaData/annualtemp.txt");
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
	
int main() {
	int chosen_year;
	int number_of_columns = 6;
	int temp_col = 4;
	double av = 0;
	int first_year = 1722;
	int last_year = 2013;
	//Uncomment this if you want to change the number of columns (i.e. if using a different, but still compatible dataset):
	/*cout << "Please enter the number of columns, this will only work for complete datasets: " << endl;
	cin >> number_of_columns;
	cout << "Please specify column to average (first is 0, last is " << (number_of_columns-1) << "): " << endl;
	cin >> temp_col;
	*/
	
	//Uncomment this if you want the temp for a specific year:
	/*cout << "Enter chosen year to count measurements: " << endl;
	cin >> chosen_year;	

	av = count_measurements_per_year(chosen_year, number_of_columns, temp_col);
	cout << "Yearly average temperature for year " << chosen_year << " is " << setprecision(2) << av << endl;
	*/
	//Uncomment below if you want a custom interval.
	/*
	cout << "Enter starting year: " << endl;
	cin >> first_year;
	cout << "Enter last year: " << endl;
	cin >> last_year;
	*/
	cout << "Computing yearly averages from the Uppsala data set, outputs in CleanData/UppsalaData/annualtemp.txt. The script might take a little while... Drink some coffee." << endl;
	output_annual_temp(first_year, last_year);
	cout << "done. Saved to CleanData/UppsalaData/annualtemp.txt." << endl;

	return 0;

}
