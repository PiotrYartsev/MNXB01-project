#include <iostream>
#include <string>
using namespace std;
class Date
{
public:
    Date() {}
    Date(string dateString)
    {
        year = strtol(dateString.substr(0, 4).c_str(), NULL, 10);
        month = strtol(dateString.substr(5, 2).c_str(), NULL, 10);
        day = strtol(dateString.substr(8, 2).c_str(), NULL, 10);
    }
    Date(int year, int month, int day)
    {
        this->year = year;
        this->day = day;
        this->month = month;
    }
    ~Date() {}
    int get_year()
    {
        return year;
    }
    int get_day()
    {
        return day;
    }
    int get_month()
    {
        return month;
    }
    int get_temp(){
        return temperature;
    }
    void set_year(int year)
    {
        this->year = year;
    }
    void set_day(int day)
    {
        this->day = day;
    }
    void set_month(int month)
    {
        this->month = month;
    }
    void set_temp(double temp)
    {
        temperature = temp;
    }
    string to_string()
    {
        return std::to_string(year) + '-' + std::to_string(month) + '-' + std::to_string(day);
    }
    int day_of_year()
    {
        if (is_leap())
        {
            int leapYearDaysByMonth[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
            return leapYearDaysByMonth[month - 1] + day;
        }
        else
        {
            int nonLeapYearDaysByMonth[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
            return nonLeapYearDaysByMonth[month - 1] + day;
        }
    }
    bool is_leap()
    {
        return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
    }

private:
    int year;
    int month;
    int day;
    double temperature = 0;
};