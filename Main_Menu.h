#pragma once
#include <bits/stdc++.h>
#include <fstream>
#include "Side_Menu.h"

class Main_Menu
{
private:
    std::string title;
    COORD cordinator;
    std::vector<Side_Menu> content;

    const vector<std::string> file_name{"to_do.dat", "diary.dat", "reminder.dat", "settings.dat"};
    const vector<std::string> main_title{"to do list", "diary", "reminders", "settings"};

public:
    friend void get_data(Main_Menu temp);
    //Setters
    bool set_title(const std::string title_value);
    bool add_content(const Side_Menu &content_value);
    bool set_cordinator(const COORD &cord);
    bool add_data_to_file();

    //Getters
    const std::string get_title() const;
    int get_content_number() const;
    COORD get_cordinator() const;
    Side_Menu get_content(int index_number) const;
    Side_Menu *const get_content_address(int index_number);
    bool get_data_from_file(std::string main_title_temp);
};

//Setters
bool Main_Menu::set_title(const std::string title_value)
{
    title = title_value;

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

bool Main_Menu::add_data_to_file()
{
    std::string temp_title = this->title;
    transform(temp_title.begin(), temp_title.end(), temp_title.begin(), ::tolower);

    int serial{0};
    for (serial = 0; serial < main_title.size(); serial++)
        if (main_title.at(serial) == temp_title)
            break;

    remove(file_name.at(serial).c_str());

    fstream myfile;
    myfile.open(file_name.at(serial).c_str(), ios::app | ios::out | ios::binary);
    if (myfile.is_open())
    {
        myfile << this->title << endl;
        myfile << this->cordinator.X << endl;
        myfile << this->cordinator.Y << endl;
        myfile << this->get_content_number() << endl;

        for (Side_Menu temp : this->content)
        {
            myfile << temp.highest_length << endl;
            myfile << temp.title << endl;
            myfile << temp.title_serial << endl;
            myfile << temp.active_status << endl;
            myfile << temp.passive_status << endl;
            myfile << temp.content.size() << endl;
            for (size_t i{0}; i < temp.get_content_size(); i++)
                myfile << temp.content.at(i) << endl;
        }

        myfile.close();
    }

    return true;
}

bool Main_Menu::get_data_from_file(std::string main_title_temp)
{
    transform(main_title_temp.begin(), main_title_temp.end(), main_title_temp.begin(), ::tolower);

    int serial{0};
    for (serial = 0; serial < main_title.size(); serial++)
        if (main_title.at(serial) == main_title_temp || to_string(serial) == main_title_temp)
            break;

    fstream myfile;
    myfile.open(file_name.at(serial).c_str(), ios::in | ios::binary | ios::app);
    myfile.seekg(0);

    int temp_size, content_size;
    std::string temp_str;

    std::getline(myfile, this->title);

    myfile >> this->cordinator.X;
    myfile >> this->cordinator.Y;

    myfile >> temp_size;

    for (; temp_size > 0; temp_size--)
    {
        Side_Menu side_temp;

        myfile >> side_temp.highest_length;

        myfile.ignore();
        getline(myfile, side_temp.title);

        myfile >> side_temp.title_serial;

        myfile >> side_temp.active_status;

        myfile >> side_temp.passive_status;

        myfile >> content_size;

        myfile.ignore();
        for (; content_size > 0; content_size--)
        {
            getline(myfile, temp_str);
            (side_temp.content).push_back(temp_str);
        }
        (this->content).push_back(side_temp);
    }

    myfile.close();

    return true;
}

//Getters

const std::string Main_Menu::get_title() const { return title; }
int Main_Menu::get_content_number() const { return content.size(); }
COORD Main_Menu::get_cordinator() const { return cordinator; }
Side_Menu Main_Menu::get_content(int index_number) const { return content.at(index_number); }
Side_Menu *const Main_Menu::get_content_address(int index_number) { return &content.at(index_number); }
