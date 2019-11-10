#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


//Define and implement a function that returns a mean temp, given a start and end year. First and last year measurements are included.
double interval_mean(int first_year = 1722, int last_year = 2013) {
	
		if (first_year < 1722) {cout << "Too early! Only measurements after 1722 available." << endl; return 1;}
		if (last_year > 2013) {cout << "Too late! Only measurements before 2013 available." << endl; return 1;}
		
		ifstream inFile;
		inFile.open("../ProcessedData/UppsalaData/annualtemp.txt", ios::in);
		double num = 0;
		double remainder = 0;
		double temp_sum = 0;
		int count = 0;
		int n = 0;
		bool in_interval = 0;
	
		
		while(inFile >> num) {
			//the remainder is useful to check which column, i.e. remainder == 0 means year and remainder == 1 means temperature. num can be both.
			remainder = (n%2);
			
			if(int(num) >= first_year && remainder == 0) {in_interval = 1;}
			if(int(num) > last_year && remainder == 0){break;}	
				
			if (remainder == 1 && in_interval) {
					temp_sum += num;
					count += 1;
					}						
			n++;
			}
			inFile.close();
			
			return (temp_sum/count);
			
}

int moving_mean_all(int first_year, int last_year, int box_interval) {
	int year = first_year;
	int length = int((last_year-first_year)/box_interval);
	cout << "length: " << length << endl;
	double arr[length];
	int k = 0;
	
	ofstream outFile2("../ProcessedData/UppsalaData/movingboxmeantemp.txt");	
		if(!outFile2) {
			std::cout << "Error" << endl;
			return 1;
			}
		
	while((year + box_interval) < last_year) {
		first_year = year;
		year += box_interval;
		cout << "from year: " << first_year << " to " << year << endl;
		arr[k] = interval_mean(first_year, year);
		cout << "entry: " << k << " temp: " << arr[k] << endl;//" year: " << year << endl;
		
		
		outFile2 << first_year << " " << year << " " << setprecision(2) << arr[k] << endl;
			
		k++;		
		}
		outFile2.close();
		cout << k << " entries stored." << endl;
		return 0;
		
}
/*
int main() {
	//Choose first year, last year and box_interval for the moving mean.
	int first_year = 1722;
	int last_year = 2013;
	int box_interval = 5;
	double result = 0.;
	//1 saves output.
	bool save_output = 1;
	bool box_mean = 0;
	
	
	result = interval_mean(first_year, last_year);
	cout << "Average temperature between " << first_year << " and " << last_year << " is: "  << setprecision(2) << result << endl;
	cout << "Commencing moving mean calculation between " << first_year << " and " << last_year << "." << endl;
	
		
	moving_mean_all(first_year, last_year, box_interval, save_output);
	cout << "Program terminated succesfully." << endl;
	cout << "Output stored in ProcessedData/UppsalaData/movingboxmeantemp.txt" << endl;
	
	return 0;
}
*/
