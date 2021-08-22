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
    static int num;
    char *title;
    char active_status;
    char passive_status;
    COORD cordinator;
    std::vector<char *> content;
    int title_serial;

public:
    Side_Menu(){
        this->active_status=char(254);
        this->passive_status=char(251);

    }
    //Setters
    bool add_object(std::string title_value, int title_serial_value);
    bool add_content(const char *content_value);
    bool set_cordinator(COORD &cordinator_value);

    //Getters
    const char *get_title() const;
    COORD get_cordinator();
    const char *get_content(int index_number) const;
    int get_title_serial();
    int get_content_size();
    char get_active_status();
    //methods
    void toggle();
};

int Side_Menu::num{0};

//Setters
bool Side_Menu::add_object(std::string title_value, int title_serial_value)
{
    title = new char[title_value.length() + 1];
    std::strcpy(title, title_value.c_str());
    title_serial = title_serial_value;

    title_serial = num++;

    return true;
}
bool Side_Menu::add_content(const char *content_value)
{
    content.push_back(new char[std::strlen(content_value) + 1]);
    std::strcpy(content.at(0), content_value);
    return true;
}
bool Side_Menu::set_cordinator(COORD &cordinator_value)
{
    cordinator = cordinator_value;

    return true;
}

//Getters

const char *Side_Menu::get_title() const { return title; }
COORD Side_Menu::get_cordinator() { return cordinator; }
const char *Side_Menu::get_content(int index_number) const { return content.at(index_number); }
int Side_Menu::get_title_serial() { return title_serial; }
int Side_Menu::get_content_size() { return content.size(); }
char Side_Menu::get_active_status(){ return this->active_status;}

//methods

void Side_Menu::toggle(){ swap(this->active_status,this->passive_status);}