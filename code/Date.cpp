#include <iostream>
#include <string>
#include <stdlib.h>
#include "Date.h"
using namespace std;

#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}
Date::Date() {}
Date::Date(string dateString)
{
    /*
     * year = strtol(dateString.substr(0, 4).c_str(), NULL, 10);
     * month = strtol(dateString.substr(5, 2).c_str(), NULL, 10);
     * day = strtol(dateString.substr(8, 2).c_str(), NULL, 10);
     */
     year = atoi(dateString.substr(0, 4).c_str());
     month = atoi(dateString.substr(5, 2).c_str());
     day = atoi(dateString.substr(8, 2).c_str());
}
Date::Date(int year, int month, int day)
{
    this->year = year;
    this->day = day;
    this->month = month;
}
Date::~Date() {}
int Date::get_year()
{
    return year;
}
int Date::get_day()
{
    return day;
}
int Date::get_month()
{
    return month;
}
int Date::get_temp()
{
    return temperature;
}
void Date::set_year(int year)
{
    this->year = year;
}
void Date::set_day(int day)
{
    this->day = day;
}
void Date::set_month(int month)
{
    this->month = month;
}
void Date::set_temp(double temp)
{
    temperature = temp;
}
string Date::to_string()
{
    return patch::to_string(year) + '-' + patch::to_string(month) + '-' + patch::to_string(day);
}
int Date::day_of_year()
{
    if (is_leap())
    {
        int leapYearDaysByMonth[13];
        leapYearDaysByMonth[0] = 0;
        leapYearDaysByMonth[1] = 31;
        leapYearDaysByMonth[2] = 60;
        leapYearDaysByMonth[3] = 91;
        leapYearDaysByMonth[4] = 121;
        leapYearDaysByMonth[5] = 152;
        leapYearDaysByMonth[6] = 182;
        leapYearDaysByMonth[7] = 213;
        leapYearDaysByMonth[8] = 244;
        leapYearDaysByMonth[9] = 274;
        leapYearDaysByMonth[10] = 305;
        leapYearDaysByMonth[11] = 335;
        leapYearDaysByMonth[12] = 366;
        return leapYearDaysByMonth[month - 1] + day;
    }
    else
    {
        int nonLeapYearDaysByMonth[13];
        nonLeapYearDaysByMonth[0] = 0;
        nonLeapYearDaysByMonth[1] = 30;
        nonLeapYearDaysByMonth[2] = 59;
        nonLeapYearDaysByMonth[3] = 90;
        nonLeapYearDaysByMonth[4] = 120;
        nonLeapYearDaysByMonth[5] = 151;
        nonLeapYearDaysByMonth[6] = 181;
        nonLeapYearDaysByMonth[7] = 212;
        nonLeapYearDaysByMonth[8] = 243;
        nonLeapYearDaysByMonth[9] = 273;
        nonLeapYearDaysByMonth[10] = 304;
        nonLeapYearDaysByMonth[11] = 334;
        nonLeapYearDaysByMonth[12] = 365;
        return nonLeapYearDaysByMonth[month - 1] + day;
    }
}
bool Date::is_leap()
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}
