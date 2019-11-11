#include <iostream>
#include <string>
#include "Date.h"
using namespace std;

Date::Date() {}
Date::Date(string dateString)
{
    year = strtol(dateString.substr(0, 4).c_str(), NULL, 10);
    month = strtol(dateString.substr(5, 2).c_str(), NULL, 10);
    day = strtol(dateString.substr(8, 2).c_str(), NULL, 10);
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
    return std::to_string(year) + '-' + std::to_string(month) + '-' + std::to_string(day);
}
int Date::day_of_year()
{
    if (is_leap())
    {
        int leapYearDaysByMonth[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
        return leapYearDaysByMonth[month - 1] + day;
    }
    else
    {
        int nonLeapYearDaysByMonth[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
        return nonLeapYearDaysByMonth[month - 1] + day;
    }
}
bool Date::is_leap()
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}
