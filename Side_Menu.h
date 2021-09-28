#pragma once
#include <bits/stdc++.h>

using namespace std;
class Side_Menu
{
private:
    int title_serial;
    vector<int> content_time, content_date;
    vector<char> active_status;
    vector<char> passive_status;
    std::string title;
    std::vector<std::string> content;
    std::string content_initialization{"Add another"};

public:
    friend class Main_Menu;

    //Constructor
    Side_Menu();

    //Destructor
    ~Side_Menu();

    //Setters
    bool set_title(const std::string title_value);
    bool add_content(const std::string content_value);
    bool add_content_time(int hour_value, int minutes_value);
    bool add_content_time(std::string time_value);
    bool add_content_date(int day_value, int month_value, int year_value);
    bool add_content_date(std::string date_value);

    //Getters
    const std::string get_title() const;
    const std::string get_content(int index_number) const;
    const int get_title_serial();
    const int get_content_size();
    const int get_completed_content_size();
    const char get_active_status(int serial);
    const int get_hour(int serial);
    const int get_minute(int serial);
    const int get_period(int serial);
    const int get_day(int serial);
    const int get_month(int serial);
    const int get_year(int serial);
    const std::string get_content_date(int serial);
    const std::string get_content_time(int serial);

    //methods
    void toggle(int serial); // For changing the current active_status
    void reset();
    void sort();
};

//Constructor

Side_Menu::Side_Menu()
{
    this->title = "Add name";
    this->content.push_back(content_initialization);
    this->active_status.push_back(char(175));
    this->passive_status.push_back(char(175));
    this->content_time.push_back(0);
    this->content_date.push_back(0);
}

//Destructor
Side_Menu::~Side_Menu() {}

//Setters
bool Side_Menu::set_title(const std::string title_value)
{
    this->title.clear();
    this->title = title_value;
    this->title.at(0) = toupper(title.at(0));

    return true;
}
bool Side_Menu::add_content(const std::string content_value)
{
    this->content.push_back(content_value);
    this->content.at(this->get_content_size() - 1).at(0) = toupper(content_value.at(0));
    this->active_status.push_back(char(254));
    this->passive_status.push_back(char(251));
    this->content_time.push_back(0);
    this->content_date.push_back(0);

    time_t now = std::time(0);
    struct tm content_time_now;
    localtime_s(&content_time_now, &now);

    this->add_content_time(content_time_now.tm_hour, content_time_now.tm_min);
    this->add_content_date(content_time_now.tm_mday, content_time_now.tm_mon + 1, content_time_now.tm_year + 1900);

    return true;
}

bool Side_Menu::add_content_time(int hour_value, int minutes_value)
{
    int period_value{0};
    int temp_hour_value{hour_value};

    if (hour_value < 24 && minutes_value < 60)
    {
        if (hour_value == 0)
            temp_hour_value = 12;

        if (hour_value > 12)
        {
            temp_hour_value = hour_value - 12;
            period_value = 1;
        }
        this->content_time.at(this->content.size() - 1) = (period_value + minutes_value * 10 + temp_hour_value * 1000);

        // cout << endl
        //      << endl
        //      << "\t\t\t\t\t\t\t" << this->content_time.size() << endl;
        return true;
    }

    return false;
}

bool Side_Menu::add_content_time(std::string time_value)
{
    int time_int_value{0};
    std::stringstream string_to_int(time_value);
    string_to_int >> time_int_value;

    this->add_content_time(time_int_value / 100, time_int_value % 100);

    return true;
}

bool Side_Menu::add_content_date(int day_value, int month_value, int year_value)
{
    this->content_date.at(this->content.size() - 1) = (day_value + month_value * 100 + year_value * 10000);

    return true;
}
bool Side_Menu::add_content_date(std::string date_value)
{
    int date_int_value{0};
    std::stringstream string_to_int(date_value);
    string_to_int >> date_int_value;

    this->content_date.at(this->content.size() - 1) = date_int_value;

    return true;
}

//Getters

const std::string Side_Menu::get_title() const { return title; }
const std::string Side_Menu::get_content(int index_number) const { return content.at(index_number); }
const int Side_Menu::get_title_serial() { return title_serial; }
const int Side_Menu::get_content_size() { return content.size(); }
const int Side_Menu::get_completed_content_size()
{
    int size{0};

    for (size_t i{0}; i < this->active_status.size(); i++)
        if (this->active_status.at(i) == char(251))
            size++;

    return size;
}
const char Side_Menu::get_active_status(int serial) { return this->active_status.at(serial); }
const int Side_Menu::get_hour(int serial) { return content_time.at(serial) / 1000; }
const int Side_Menu::get_minute(int serial) { return (content_time.at(serial) / 10) % 100; }
const int Side_Menu::get_period(int serial) { return content_time.at(serial) % 10; }
const int Side_Menu::get_day(int serial) { return content_date.at(serial) % 100; }
const int Side_Menu::get_month(int serial) { return (content_date.at(serial) / 100) % 100; }
const int Side_Menu::get_year(int serial) { return content_date.at(serial) / 10000; }
const std::string Side_Menu::get_content_time(int serial)
{
    string content_time_str = to_string(this->get_hour(serial)) + ':';

    if (this->get_minute(serial) > 10)
        content_time_str += to_string(this->get_minute(serial));
    else
        content_time_str += '0' + to_string(this->get_minute(serial));

    if (this->get_period(serial) == 0)
        content_time_str += " AM";
    else
        content_time_str += " PM";

    return content_time_str;
}
const std::string Side_Menu::get_content_date(int serial)
{
    string content_date_str = to_string(this->get_day(serial)) + '-';

    if (this->get_month(serial) > 10)
        content_date_str += to_string(this->get_month(serial));
    else
        content_date_str += '0' + to_string(this->get_month(serial));

    content_date_str += '-' + to_string(this->get_year(serial));

    return content_date_str;
}

//methods
void Side_Menu::toggle(int serial) { swap(this->active_status.at(serial), this->passive_status.at(serial)); }

void Side_Menu::reset()
{
    this->~Side_Menu();
    new (this) Side_Menu;
}

void Side_Menu::sort()
{
    Side_Menu temp;
    int serial{1};

    temp.title = this->title;
    temp.title_serial = this->title_serial;

    for (size_t i{0}; i < this->get_content_size(); i++)
    {
        if (this->active_status.at(i) == char(254))
        {
            temp.add_content(this->content.at(i));
            temp.active_status.at(serial) = this->active_status.at(i);
            temp.passive_status.at(serial) = this->passive_status.at(i);
            serial++;
        }
    }
    for (size_t i{0}; i < this->get_content_size(); i++)
    {
        if (this->active_status.at(i) == char(251))
        {
            temp.add_content(this->content.at(i));
            temp.active_status.at(serial) = this->active_status.at(i);
            temp.passive_status.at(serial) = this->passive_status.at(i);
            serial++;
        }
    }

    this->reset();
    *this = temp;
    temp.reset();
}
