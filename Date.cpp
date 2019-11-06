#include <iostream>
#include <string>
using namespace std;
class Date
{
public:
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
    void set_year(int year)
    {
        this->year = year;
    }
    void set_day()
    {
        this->day = day;
    }
    void set_month()
    {
        this->month = month;
    }
    string toString()
    {
        return to_string(year) + '-' + to_string(month) + '-' + to_string(day);
    }

private:
    int year;
    int month;
    int day;
};