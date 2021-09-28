#pragma once
#include <bits/stdc++.h>
#include <fstream>
#include "side_menu.h"

class Main_Menu
{
private:
    static int total_main_menu_constructed;

    COORD cordinator;

    std::string title;
    std::vector<Side_Menu> content;

    const vector<std::string> main_menu_title{"To Do List", "Diary", "Reminders", "Settings"};
    const vector<std::string> main_menu_description{"Here see your tasks", "See your daily events", "See your reminders", "Personalize your settings"};
    const vector<std::string> file_name{"to_do.dat", "diary.dat", "reminder.dat", "settings.dat"};
    const vector<std::string> side_menu_title{"Add task", "Add event", "Add event"};
    const vector<std::string> side_menu_description{"Add an task", "Add about your day", "Add an event that you want to be reminded"};

public:
    //Constructor
    Main_Menu();
    //Destructor
    ~Main_Menu();

    //Setters
    bool set_cordinator(const COORD cordinator_value);
    bool set_title(const std::string title_value);
    bool add_content(const Side_Menu &content_value);
    bool add_data_to_file();

    //Getters
    const std::string get_title() const;
    const std::string get_description() const;
    int get_content_number() const;
    int get_highest_main_description_length() const;
    COORD get_cordinator() const;
    Side_Menu get_content(int index_number) const;
    Side_Menu *const get_content_reference(int index_number);
    bool get_data_from_file();
};

int Main_Menu::total_main_menu_constructed{0};

//Constructor
Main_Menu::Main_Menu()
{
    total_main_menu_constructed++;

    this->title = main_menu_title.at((total_main_menu_constructed - 1) % 4);
    if ((total_main_menu_constructed - 1) % 4 != 3)
    {

        Side_Menu side_menu_temp;
        side_menu_temp.title_serial = 0;
        side_menu_temp.active_status.at(0) = (char(175));
        side_menu_temp.passive_status.at(0) = (char(175));
        side_menu_temp.title = side_menu_title.at((total_main_menu_constructed - 1) % 4);
        side_menu_temp.content.at(0) = (side_menu_description.at((total_main_menu_constructed - 1) % 4));

        this->content.push_back(side_menu_temp);
    }
}

//Destructor
Main_Menu::~Main_Menu() {}

//Setters

bool Main_Menu::set_cordinator(const COORD cordinator_value)
{
    cordinator = cordinator_value;

    return true;
}

bool Main_Menu::set_title(const std::string title_value)
{
    title = title_value;

    return true;
}
bool Main_Menu::add_content(const Side_Menu &content_value)
{
    (this->content).push_back(content_value);
    (this->content.at(this->content.size() - 1)).title_serial = this->content.size() - 1;

    return true;
}

bool Main_Menu::add_data_to_file()
{
    int serial{0};
    for (serial = 0; serial < main_menu_title.size(); serial++)
        if (main_menu_title.at(serial) == this->title)
            break;

    remove(file_name.at(serial).c_str());

    fstream myfile;
    myfile.open(file_name.at(serial).c_str(), ios::app | ios::out | ios::binary);
    if (myfile.is_open())
    {
        this->content.size() > 0 ? myfile << this->content.size() - 1 << endl : myfile << 0 << endl;

        for (Side_Menu temp : this->content)
        {
            if (temp.title_serial != 0)
            {
                myfile << temp.title << endl;
                myfile << temp.content.size() - 1 << endl;

                for (size_t i{0}; i < temp.get_content_size(); i++)
                {
                    if (temp.content.at(i) != temp.content_initialization)
                    {
                        myfile << temp.content.at(i) << endl;
                        myfile << temp.active_status.at(i) << endl;
                        myfile << temp.passive_status.at(i) << endl;
                        myfile << temp.content_time.at(i) << endl;
                        myfile << temp.content_date.at(i) << endl;
                    }
                }
            }
        }
        myfile.close();
    }

    return true;
}

//Getters

const std::string Main_Menu::get_title() const { return title; }
const std::string Main_Menu::get_description() const
{

    int serial{0};
    for (serial = 0; serial < main_menu_title.size(); serial++)
        if (main_menu_title.at(serial) == this->title)
            break;
    return main_menu_description.at(serial);
}
int Main_Menu::get_content_number() const { return content.size(); }
int Main_Menu::get_highest_main_description_length() const
{
    int temp_length{0};
    for (auto str : main_menu_description)
        if (str.length() > temp_length)
            temp_length = str.length();

    return temp_length;
}
COORD Main_Menu::get_cordinator() const { return cordinator; }
Side_Menu Main_Menu::get_content(int index_number) const { return content.at(index_number); }
Side_Menu *const Main_Menu::get_content_reference(int index_number) { return &content.at(index_number); }

bool Main_Menu::get_data_from_file()
{
    static int get_data_method_called{0};
    int serial = (get_data_method_called++ % 4);

    fstream myfile;
    myfile.open(file_name.at(serial).c_str(), ios::in | ios::binary | ios::app);
    myfile.seekg(0);

    int temp_size, content_size;
    std::string temp_str;

    //Reading Start

    myfile >> temp_size;

    myfile.ignore();
    if (temp_size > 0)
    {
        int serial{1};

        for (; temp_size > 0; temp_size--)
        {
            Side_Menu side_temp;

            getline(myfile, side_temp.title);
            // side_temp.title.at(0) = toupper(side_temp.title.at(0));

            side_temp.title_serial = serial++;

            myfile >> content_size;

            int content_serial{1};
            myfile.ignore();

            for (; content_size > 0; content_size--)
            {
                getline(myfile, temp_str);
                side_temp.add_content(temp_str);

                char temp_char{}, temp_char_2{};
                myfile >> side_temp.active_status.at(content_serial);
                myfile.ignore();
                myfile >> side_temp.passive_status.at(content_serial);
                myfile >> side_temp.content_time.at(content_serial);
                myfile >> side_temp.content_date.at(content_serial);
                myfile.ignore();

                content_serial++;
            }
            (this->content).push_back(side_temp);
        }
    }

    myfile.close();

    return true;
}
