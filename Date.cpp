#include <iostream>
class Date
{
public:
    Date(string dateString)
    {
        year = strtol(dateString.substr(0, 4));
        month = strtol(dateString.substr(5, 2));
        day = strtol(dateString.substr(8, 2));
    }
    Date(int year, int month, int day)
    {
        this.year = year;
        this.day = day;
        this.month = month;
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
        this.year = year;
    }
    void set_day()
    {
        this.day = day;
    }
    void set_month()
    {
        this.month = month;
    }

private:
    int year;
    int month;
    int day;
}