#include <iostream>
#include "tempTrender.h"

// include C++ STL headers 
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TH2.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TString.h>
#include <TRandom.h>
#include <TGraph.h>
#include <TGaxis.h>
#include <TLegend.h>

#include "annualtemp.cpp"
#include "movingmean.cpp"
#include "tempYearplotandpred.cpp"

tempTrender::tempTrender(string filePath) {
	cout << "The user supplied " << filePath << " as the path to the data file." << endl;
	cout << "You should probably store this information in a member variable of the class. Good luck with the project! :)" << endl;
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
	





