#pragma once
#include <bits/stdc++.h>
#include <fstream>
#include "side_menu.h"

class Main_Menu
{
private:
    static int total_main_menu_constructed;
    static string file_directory;

    COORD coordinate;

    std::string title;
    std::vector<Side_Menu> content;

    const vector<std::string> main_menu_title{"To Do List", "Diary", "Reminders", "Settings"};
    const vector<std::string> main_menu_description{"Manage your tasks", "Manage your daily events", "Manage your reminders", "Personalize your settings"};
    const vector<std::string> file_name{"to_do.dat", "diary.dat", "reminder.dat", "settings.dat"};
    const vector<std::string> side_menu_title{"Create a list", "Create a list", "Create a list"};
    const vector<std::string> side_menu_description{"Add an task", "Add about your day", "Add an event that you want to be reminded"};

public:
    // Constructor
    Main_Menu();
    // Destructor
    ~Main_Menu();

    // Setters
    bool set_coordinate(const COORD coordinate_value);
    bool set_title(const std::string title_value);
    bool add_content(const Side_Menu &content_value);
    bool add_data_to_file();

    // Getters
    const std::string get_title() const;
    const std::string get_description() const;
    int get_content_number() const;
    int get_highest_main_description_length() const;
    COORD get_coordinate() const;
    Side_Menu get_content(int index_number) const;
    Side_Menu *const get_content_reference(int index_number);
    bool get_data_from_file();

    // Methods
    void delete_content(int serial);
};

int Main_Menu::total_main_menu_constructed{0};
string Main_Menu::file_directory{"userData/"};

// Constructor
Main_Menu::Main_Menu()
{
    CreateDirectory(file_directory.c_str(), NULL); // Creating directory

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

// Destructor
Main_Menu::~Main_Menu() {}

// Setters

bool Main_Menu::set_coordinate(const COORD coordinate_value)
{
    coordinate = coordinate_value;

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

    remove((file_directory + file_name.at(serial)).c_str());

    fstream myFile;
    myFile.open((file_directory + file_name.at(serial)).c_str(), ios::app | ios::out | ios::binary);
    if (myFile.is_open())
    {
        this->content.size() > 0 ? myFile << this->content.size() - 1 << endl : myFile << 0 << endl;

        for (Side_Menu temp : this->content)
        {
            if (temp.title_serial != 0)
            {
                myFile << temp.title << endl;
                myFile << temp.content.size() - 1 << endl;

                for (size_t i{0}; i < temp.get_content_size(); i++)
                {
                    if (temp.content.at(i) != temp.content_initialization)
                    {
                        if (serial == 1 && i == 2)
                        {
                            int newline_count{0};
                            string temp_content_string = temp.content.at(i);

                            // cout<<temp_content_string.length()<<endl;
                            // Sleep(5000);

                            for (size_t j{0}; j < temp_content_string.length(); j++)
                                if (temp_content_string.at(j) == '\n')
                                    myFile << j - newline_count++ << " ";

                            if (newline_count == 0)
                                myFile << temp_content_string.length() << " ";

                            myFile << endl;

                            for (size_t j{0}; j < temp_content_string.length(); j++)
                                if (temp_content_string.at(j) != '\n')
                                    myFile << temp_content_string.at(j);

                            myFile << endl;
                        }
                        else
                            myFile << temp.content.at(i) << endl;

                        myFile << temp.active_status.at(i) << endl;
                        myFile << temp.passive_status.at(i) << endl;
                        myFile << temp.content_time.at(i) << endl;
                        myFile << temp.content_date.at(i) << endl;
                    }
                }
            }
        }
        myFile.close();
    }

    return true;
}

// Getters

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
COORD Main_Menu::get_coordinate() const { return coordinate; }
Side_Menu Main_Menu::get_content(int index_number) const { return content.at(index_number); }
Side_Menu *const Main_Menu::get_content_reference(int index_number) { return &content.at(index_number); }

bool Main_Menu::get_data_from_file()
{
    static int get_data_method_called{0};
    int sub_menu_serial = (get_data_method_called++ % 4);

    fstream myFile;
    myFile.open((file_directory + file_name.at(sub_menu_serial)).c_str(), ios::in | ios::binary | ios::app);
    myFile.seekg(0);

    int temp_size, content_size;
    std::string temp_str;

    // Reading Start

    myFile >> temp_size;

    myFile.ignore();
    if (temp_size > 0)
    {
        int serial{1};

        for (; temp_size > 0; temp_size--)
        {
            Side_Menu side_temp;

            getline(myFile, side_temp.title);
            // side_temp.title.at(0) = toupper(side_temp.title.at(0));

            side_temp.title_serial = serial++;

            myFile >> content_size;

            int content_serial{1};
            myFile.ignore();

            for (; content_size > 0; content_size--)
            {
                if (sub_menu_serial == 1 && content_size == 1)
                {
                    vector<int> diary_content_serial;
                    int number{0};
                    string diary_content_serial_string;
                    string diary_content_string;

                    getline(myFile, diary_content_serial_string);

                    diary_content_serial.clear();

                    for (size_t j{0}; j < diary_content_serial_string.length(); j++)
                    {
                        if (diary_content_serial_string.at(j) >= '0' && diary_content_serial_string.at(j) <= '9')
                            number = number * 10 + (diary_content_serial_string.at(j) - '0');
                        else if (diary_content_serial_string.at(j) == ' ' && number > 0)
                        {
                            diary_content_serial.push_back(number);
                            number = 0;
                        }
                    }

                    getline(myFile, temp_str);

                    int t{0};

                    for (size_t j{0}; j < temp_str.length(); j++)
                    {
                        if (diary_content_serial.at(t) == j && t < diary_content_serial.size())
                        {
                            diary_content_string += '\n';
                            int temp_int = t + 1;
                            for (int k{temp_int}; k < diary_content_serial.size(); k++)
                            {
                                if (diary_content_serial.at(t) == diary_content_serial.at(k))
                                {
                                    t++;
                                    diary_content_string += '\n';
                                }
                                else
                                {
                                    t++;
                                    break;
                                }
                            }
                        }
                        diary_content_string += temp_str.at(j);
                    }
                    // cout << diary_content_string.length() << endl;

                    if (t < diary_content_serial.size() && diary_content_serial.at(t) == temp_str.length())
                    {
                        diary_content_string += '\n';
                        // cout << diary_content_serial.size() << "\t" << t << "\t" << diary_content_serial.at(t) << endl;
                        // cout << diary_content_string.length() << endl;
                        // Sleep(3000);
                    }

                    side_temp.add_content(diary_content_string);
                }
                else
                {
                    getline(myFile, temp_str);
                    side_temp.add_content(temp_str);
                }

                myFile >> side_temp.active_status.at(content_serial);
                myFile.ignore();
                myFile >> side_temp.passive_status.at(content_serial);
                myFile >> side_temp.content_time.at(content_serial);
                myFile >> side_temp.content_date.at(content_serial);
                myFile.ignore();

                content_serial++;
            }
            (this->content).push_back(side_temp);
        }
    }

    myFile.close();

    return true;
}

// Methods

void Main_Menu::delete_content(int serial)
{
    this->content.erase(this->content.begin() + serial);
}
