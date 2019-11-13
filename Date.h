#include <iostream>
#include <string>

class Date
{
public:
    Date();
    Date(std::string dateString);
    Date(int year, int month, int day);
    ~Date();
    int get_year();
    int get_day();
    int get_month();
    int get_temp();
    void set_year(int year);
    void set_day(int day);
    void set_month(int month);
    void set_temp(double temp);
    std::string to_string();
    int day_of_year();
    bool is_leap();

private:
    int year;
    int month;
    int day;
    double temperature = 0;
};