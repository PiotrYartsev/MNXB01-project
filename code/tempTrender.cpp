#include <iostream>
#include "tempTrender.h"

// include C++ STL headers 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
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

//For the tempPerYear(int) function
#include "annualtemp.cpp"
#include "tempYearplotandpred.cpp"

//For the HotCold() functions
#include <vector>
#include <utility>
#include "dateOfPeakTemp_Upp.cpp" //Fix before we can uncomment.
#include "TH1I.h"


tempTrender::tempTrender(string filePath) {
	cout << "The user supplied " << filePath << " as the path to the data file." << endl;
	cout << "You should probably store this information in a member variable of the class. Good luck with the project! :)" << endl;
	this->filePath = filePath;
}

/* 
Root function to plot histograms of the annual average temperatures from the annualtemp.txt data set, and to extrapolate temperature to a year given by user input.
* Make sure to run annualtemp.cpp first, or just call project() if rootlogon.C works as it should.
* By: Leo Zethraeus
*/

//Input: the year you want to extrapolate to, or estimate the future temperature, in other words. Output: the estimated temperature that year.
//_______		
void tempTrender::tempPerYear(int yearToExtrapolate){
	int first_year = 1722;
	int last_year = 2013;
	
	ifstream processedfile("../ProcessedData/UppsalaData/annualtemp.txt"); // Check if file exists
	if(!processedfile){
		output_annual_temp(first_year, last_year);}
	processedfile.close();
	
	tempYearplotandpred(yearToExtrapolate);	
}

// To set and plot the histogram for hottest and coldest date in Uppsala.
void tempTrender::hotCold_Upp() {
	int location_specified = 1;
	int mode = 1;
	int start_year = 1722;
	ifstream inFile(filePath.c_str()); // Check if file exists
	if(!inFile){
        std::cout << "No such file";
		return;
    }
	peak_temp_Upp(inFile, start_year, mode, location_specified);
	inFile.close();
}
/*
// To set and plot the histogram for hottest and coldest date other than Uppsala.
void tempTrender::hotCold(){
	int location_specified = 1;
	int mode = 1;
	int start_year = 1722;
	peak_temp_Upp(inFile, start_year, mode, location_specified);
}
*/
