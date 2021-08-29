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
    COORD cordinator;
    std::vector<Side_Menu> content;

public:
    //Setters
    bool set_title(const std::string title_value);
    bool add_content(const Side_Menu &content_value);
    bool set_cordinator(const COORD &cord);
    bool add_user_data_to_file(Main_Menu &user);

    //Getters
    const char *get_title() const;
    COORD get_cordinator() const;
    Side_Menu get_content(int index_number) const;
    int get_content_number() const;
    Side_Menu *const get_content_address(int index_number);
};

//Setters
bool Main_Menu::set_title(const std::string title_value)
{
    title = new char[title_value.length() + 1];
    std::strcpy(title, title_value.c_str());

    return true;
}
bool Main_Menu::add_content(const Side_Menu &content_value)
{
    content.push_back(content_value);

    return true;
}
bool Main_Menu::set_cordinator(const COORD &cord)
{
    cordinator = cord;

    return 1;
}
bool Main_Menu::add_user_data_to_file(Main_Menu &user)
{
    remove("user_details.dat");
    fstream myfile;
    myfile.open("user_details.dat", ios::app | ios::out | ios::binary);
    if (myfile.is_open())
    {
        myfile.write(reinterpret_cast<char *>(&user), sizeof(user));
        myfile.close();
    }

    return true;
}

//Getters

const char *Main_Menu::get_title() const { return title; }
COORD Main_Menu::get_cordinator() const { return cordinator; }
Side_Menu Main_Menu::get_content(int index_number) const { return content.at(index_number); }
int Main_Menu::get_content_number() const { return content.size(); }
Side_Menu *const Main_Menu::get_content_address(int index_number) { return &content.at(index_number); }
