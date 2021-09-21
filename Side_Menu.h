#pragma once
#include <bits/stdc++.h>
#include "Main_Menu.h"

using namespace std;
class Side_Menu
{
private:
    std::string title;
    int title_serial;
    vector<char> active_status;
    vector<char> passive_status;
    std::vector<std::string> content;
    std::string content_initialization{"Add something here"};

public:
    friend class Main_Menu;

    //Constructor
    Side_Menu();

    //Destructor
    ~Side_Menu();

    //Setters
    bool set_title(const std::string title_value);
    bool add_content(const std::string content_value);

    //Getters
    const std::string get_title() const;
    const std::string get_content(int index_number) const;
    const int get_title_serial();
    const int get_content_size();
    const char get_active_status(int serial);

    //methods
    void toggle(int serial); // For changing the current active_status
    void reset();
    void sort();
};

//Constructor

Side_Menu::Side_Menu()
{
    this->content.push_back(content_initialization);
    this->active_status.push_back(char(254));
    this->passive_status.push_back(char(251));
}

//Destructor
Side_Menu::~Side_Menu() {}

//Setters
bool Side_Menu::set_title(const std::string title_value)
{
    this->title = title_value;
    this->title.at(0) = toupper(title.at(0));

    return true;
}
bool Side_Menu::add_content(const std::string content_value)
{
    if (this->content.at(0) == content_initialization)
        this->content.at(0) = content_value;

    else
    {
        this->content.push_back(content_value);
        this->active_status.push_back(char(254));
        this->passive_status.push_back(char(251));
    }

    this->content.at(this->get_content_size() - 1).at(0) = toupper(content_value.at(0));

    return true;
}

//Getters

const std::string Side_Menu::get_title() const { return title; }
const std::string Side_Menu::get_content(int index_number) const { return content.at(index_number); }
const int Side_Menu::get_title_serial() { return title_serial; }
const int Side_Menu::get_content_size() { return content.size(); }
const char Side_Menu::get_active_status(int serial) { return this->active_status.at(serial); }

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
    int serial{0};

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
}
