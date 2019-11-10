
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Date.cpp"
using namespace std;
/* This script takes an input file, and creates an output with the year and the hottest and coldest date.
   Design for input format of Uppsala.
   Usage:
   ./dateOfPeakTemp [mode]
   For example:
   ./dateOfPeakTemp 1
   Mode:
   1: Daily average temperature according to observations. 
   2: Daily average temperatures corrected for the urban effect.
*/
void read_file(int start_year, int mode)
{

    //Choose path to file
    std::ifstream inFile("CleanData/datasets/uppsala_tm_1722-2013.dat");
    if (!inFile)
    {
        std::cout << "Not in file";
        return;
    }

    double num = 0.;
    int year = 0;
    int month = 0;
    int day = 0;
    double temp1 = 0;
    double temp2 = 0;
    double temp = 0;
    int location = 0;
    int n = 0;
    int remainder = 0;
    int index = 0;
    Date hottest = Date();
    Date coldest = Date();

    while (!inFile.eof())
    {
        inFile >> year >> month >> day >> temp1 >> temp2 >> location;
        //cout << year<< month <<day << temp1 << temp2 << location<< endl;
        if (location == 1)
        {
            if (year > start_year)
            {

                cout << "Coldest temperature for " << start_year << " year is " << coldest.get_temp() << ", which is at " << coldest.to_string() << ", day of year " << coldest.day_of_year() << "\n";
                cout << "Hottest temperature for " << start_year << " year is " << hottest.get_temp() << ", which is at " << hottest.to_string() << ", day of year " << hottest.day_of_year() << "\n";
                start_year = year;
                hottest = Date(year, month, day);
                coldest = Date(year, month, day);
            }
            if (mode == 1)
                temp = temp1;
            else
                temp = temp2;
            if (temp > hottest.get_temp())
            {
                hottest = Date(year, month, day);
                hottest.set_temp(temp);
            }
            if (temp < coldest.get_temp())
            {
                coldest = Date(year, month, day);
                coldest.set_temp(temp);
            }
        }
        else
    }
}
int main(int argc, char *argv[])
{
    int chosen_year;
    int number_of_columns = 6;
    int temp_col = 4;
    double av = 0;
    int start_year = 1722;
    int last_year = 2013;
    int mode = strtol(argv[1],NULL,10);

    read_file(start_year, mode);

    return 0;
}
