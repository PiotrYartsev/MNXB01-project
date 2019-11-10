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