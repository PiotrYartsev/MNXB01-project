
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <utility>
#include "Date.cpp"
using namespace std;
/* This script takes an input file, and creates an output with the year and the hottest and coldest date.
   Now design for input format other than Uppsala.
   Usage:
   ./dateOfPeakTemp [location]
   For example:
   ./dateOfPeakTemp Lund
*/

int main(int argc, char *argv[])
{

	string dirName = argv[1];
	dirName = "smhi-opendata_" + dirName;
	cout << dirName << endl;
	string fileNameTemp = "CleanData/datasets/" + dirName + "/data_temp_" + dirName + ".txt";
	cout << fileNameTemp << endl;
	string fileNameDate = "CleanData/datasets/" + dirName + "/data_date_" + dirName + ".txt";
	cout << fileNameDate << endl;
	vector<double> temp;
	vector<Date> date;
	vector<int> indexYear;
	ifstream fileTemp(fileNameTemp);
	while (!fileTemp.eof())
	{

		double t;
		fileTemp >> t;
		temp.push_back(t);
	}
	ifstream fileDate(fileNameDate);

	string ds;
	fileDate >> ds;
	Date d = Date(ds);
	date.push_back(d);
	int year = d.get_year();
	int counterIndexYear = 1;
	indexYear.push_back(0);
	while (!fileDate.eof())
	{
		fileDate >> ds;
		Date d = Date(ds);
		if (year != d.get_year())
		{
			year = d.get_year();
			indexYear.push_back(counterIndexYear);
		}
		date.push_back(d);
		counterIndexYear++;
	}
	indexYear.push_back(counterIndexYear - 1);
	/*
	cout << "size: " << indexYear.size() << endl;
	for (int i = 1; i < indexYear.size(); ++i)
		cout << i << " " << indexYear[i] << ": " << date.at(indexYear[i] - 1).get_year() << " and " << date.at(indexYear[i]).get_year() << endl;

	cout << indexYear.back() << ' ' << date.size() << endl;
	*/
	for (int i = 0; i < indexYear.size() - 1; ++i)
	{
		auto minmax = minmax_element(temp.begin() + indexYear.at(i), temp.begin() + indexYear.at(i + 1) - 1);
		cout << "Coldest temperature for " << date.at(indexYear[i]).get_year() << " year is " << *minmax.first << ", which is at " << date.at(minmax.first - temp.begin()).toString() << "\n";
		cout << "Hottest temperature for " << date.at(indexYear[i]).get_year() << " year is " << *minmax.second << ", which is at " << date.at(minmax.second - temp.begin()).toString() << "\n";
	}

	//auto minmax = minmax_element(temp.begin(), temp.end());
	//cout << "Coldest temperature is " << *minmax.first << " at index " << minmax.first - temp.begin() << ", which is at " << date.at(minmax.first - temp.begin()) << "\n";
	//cout << "Hottest temperature is " << *minmax.second << " at index " << minmax.second - temp.begin() << ", which is at " << date.at(minmax.second - temp.begin()) << "\n";

	return 0;
}
