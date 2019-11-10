#include <iostream>
<<<<<<< HEAD
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
	





=======
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

// To set and plot the histogram for hottest and coldest date in Uppsala.
void tempTrender::hotCold_Upp() {
	int location_specified = 1;
	int mode = 1;
	int start_year = 1722;
	peak_temp_Upp(inFile, start_year, mode, location_specified);
}

// To set and plot the histogram for hottest and coldest date other than Uppsala.
void tempTrender::hotCold(){
	int location_specified = 1;
	int mode = 1;
	int start_year = 1722;
	peak_temp_Upp(inFile, start_year, mode, location_specified);
}
>>>>>>> 32c010efe60d2a4697a5e85f8946d897d068a1cd
