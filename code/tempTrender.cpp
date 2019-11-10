#include <iostream>
#include "tempTrender.h"
#include "../dateOfPeakTemp_Upp.cpp"
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
	peak_temp(inFile, 1722, 1);
	
}

