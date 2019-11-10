#include <iostream>
#include <vector>
#include <utility>
#include "tempTrender.h"
#include "../dateOfPeakTemp_Upp.cpp"
#include "TH1I.h"

using namespace std;

tempTrender::tempTrender(string filePath) {
	cout << "The user supplied " << filePath << " as the path to the data file." << endl;
	//cout << "You should probably store this information in a member variable of the class. Good luck with the project! :)" << endl;
    ifstream inFile(filePath);
	if (!inFile)
    {
        std::cout << "No such file";
		return;
    }
	else{
		this->inFile.swap(inFile);
	}
}

void tempTrender::hotCold_Upp() {
	int location_specified = 1;
	int mode = 1;
	int start_year = 1722;
	peak_temp(inFile, start_year, mode, location_specified);
}

/* 
Root function to plot histograms of the annual average temperatures from the annualtemp.txt data set, and to extrapolate temperature to a year given by user input.
* Make sure to run annualtemp.cpp and movingmean.cpp first, in that order.
* By: Leo Zethraeus
*/

//Input: the year you want to extrapolate to, or estimate the future temperature, in other words. Output: the estimated temperature that year.
//_______		
void tempTrender::tempPerYear(int yearToExtrapolate){
	int first_year = 1722;
	int last_year = 2013;
	int box_interval = 5;
	
	ifstream processedfile("../ProcessedData/UppsalaData/annualtemp.txt"); // Check if file exists
	if(!processedfile){
		output_annual_temp(first_year, last_year);}
	processedfile.close();
	ifstream movingmeanfile("../ProcessedData/UppsalaData/movingboxmeantemp.txt"); // Check if file exists
	if(!movingmeanfile){
		moving_mean_all(first_year, last_year, box_interval);}
		movingmeanfile.close();
	
	tempYearplotandpred(yearToExtrapolate);	
	}

