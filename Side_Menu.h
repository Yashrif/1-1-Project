#pragma once
#include <bits/stdc++.h>
#include "Main_Menu.h"

using namespace std;
class Side_Menu
{
private:
    static int highest_length;

    std::string title;
    int title_serial;
    char active_status, passive_status;
    std::vector<std::string> content;

    std::string content_initialization{"Add something here"};

public:
    friend class Main_Menu;
    Side_Menu()
    {
        this->active_status = char(254);
        this->passive_status = char(251);
        this->content.push_back(content_initialization);
    }
    //Setters;
    bool set_title(const std::string title_value);
    bool add_content(const std::string content_value);

    //Getters
    const std::string get_title() const;
    const std::string get_content(int index_number) const;
    const int get_title_serial();
    const int get_content_size();
    const int get_highest_length();
    const char get_active_status();

    //methods
    void toggle(); // For changing the current status
};

int Side_Menu::highest_length{0};

//Setters
bool Side_Menu::set_title(const std::string title_value)
{
    title = title_value;

    return true;
}
bool Side_Menu::add_content(const std::string content_value)
{
    if (this->content.at(0) == content_initialization)
        this->content.at(0) = content_value;
    else
        content.push_back(content_value);

    if ((content_value).length() > highest_length)
        highest_length = (content_value).length();

    return true;
}

//Getters

const std::string Side_Menu::get_title() const { return title; }
const std::string Side_Menu::get_content(int index_number) const { return content.at(index_number); }
const int Side_Menu::get_title_serial() { return title_serial; }
const int Side_Menu::get_content_size() { return content.size(); }
const int Side_Menu::get_highest_length() { return highest_length; }
const char Side_Menu::get_active_status() { return this->active_status; }

//methods
void Side_Menu::toggle() { swap(this->active_status, this->passive_status); }