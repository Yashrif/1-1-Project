#pragma once
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <chrono>
#include "Side_Menu.h"
using namespace std;
class Main_Menu
{
private:
    char *title;
    bool content_display_status;
    COORD cordinator;
    std::vector<Side_Menu> content;

public:
    //Setters
    bool add_object(std::string title_value, int content_display_status_value);
    bool add_user_data_to_file(Main_Menu *user);
    bool add_content(const Side_Menu &content_value);
    bool set_cordinator(COORD &cord);
    bool set_content_display_status(int content_display_status_value);

    //Getters
    const char *get_title() const;
    bool get_content_display_status(); // main panel-0+ , sub panel - same as main panel's content_display_status
    COORD get_cordinator();
    Side_Menu get_content(int index_number) const;
    Side_Menu *get_content_address(int index_number);
    int get_content_number();
};

//Setters
bool Main_Menu::add_object(std::string title_value, int content_display_status_value)
{
    title = new char[title_value.length() + 1];
    std::strcpy(title, title_value.c_str());
    content_display_status = content_display_status_value;

    return true;
}
bool Main_Menu::add_content(const Side_Menu &content_value)
{
    content.push_back(content_value);

    return true;
}

bool Main_Menu::add_user_data_to_file(Main_Menu *user)
{
    remove("user_details.dat");
    fstream myfile;
    myfile.open("user_details.dat", ios::app | ios::out | ios::binary);
    if (myfile.is_open())
    {
        myfile.write(reinterpret_cast<char *>(user), sizeof(*user));
        myfile.close();
    }

    return true;
}
bool Main_Menu::set_cordinator(COORD &cord)
{
    cordinator = cord;

    return 1;
}
bool Main_Menu::set_content_display_status(int content_display_status_value)
{
    content_display_status = content_display_status_value;

    return true;
}

//Getters

const char *Main_Menu::get_title() const { return title; }
bool Main_Menu::get_content_display_status() { return content_display_status; }
COORD Main_Menu::get_cordinator() { return cordinator; }
Side_Menu Main_Menu::get_content(int index_number) const { return content.at(index_number); }
int Main_Menu::get_content_number() { return content.size(); }
Side_Menu *Main_Menu::get_content_address(int index_number) { return &content.at(index_number); }
