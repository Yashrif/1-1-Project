#pragma once
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <chrono>
using namespace std;
class Side_Menu
{
private:
    static int size;
    static int highest_length;

    char *title;
    int title_serial;
    char active_status, passive_status;
    std::vector<char *> content;

public:
    Side_Menu()
    {
        this->active_status = char(254);
        this->passive_status = char(251);
        title_serial = ++this->size;
    }
    //Setters;
    bool set_title(const std::string title_value);
    bool add_content(const char *content_value);

    //Getters
    const string get_title() const;
    const string get_content(int index_number) const;
    const int get_title_serial();
    const int get_content_size();
    const int get_highest_length();
    const char get_active_status();
    
    //methods
    void toggle(); // For changing the current status
};

int Side_Menu::size{0};
int Side_Menu::highest_length{0};

//Setters
bool Side_Menu::set_title(const std::string title_value)
{
    title = new char[title_value.length() + 1];
    std::strcpy(title, title_value.c_str());

    return true;
}
bool Side_Menu::add_content(const char *content_value)
{
    content.push_back(new char[std::strlen(content_value) + 1]);
    std::strcpy(content.at(content.size() - 1), content_value);

    if (strlen(content_value) > highest_length)
        highest_length = strlen(content_value);

    return true;
}

//Getters

const string Side_Menu::get_title() const { return title; }
const string Side_Menu::get_content(int index_number) const { return content.at(index_number); }
const int Side_Menu::get_title_serial() { return title_serial; }
const int Side_Menu::get_content_size() { return content.size(); }
const int Side_Menu::get_highest_length() { return highest_length; }
const char Side_Menu::get_active_status() { return this->active_status; }

//methods
void Side_Menu::toggle() { swap(this->active_status, this->passive_status); }