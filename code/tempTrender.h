#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>
#include <fstream>


class tempTrender {
	public:
	tempTrender(std::string filePath); //Construct using the specified file
	~tempTrender() {} //Destructor
	std::string filePath;

	void tempPerYear(int yearToExtrapolate);  //Make a histogram of average temperature per year, then fit and extrapolate to the given year
	//void hotCold(); //Make a histogram of the hottest and coldest day of the year
	void hotCold_Upp(); //Make a histogram of the hottest and coldest day of the year
		
};

#endif
