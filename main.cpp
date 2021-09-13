#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <chrono>
#include "user_funcion.h"
#include "Main_Menu.h"
#include "Side_Menu.h"
using namespace std;

int main()
{
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

    int console_width{0}, console_height{0};
    vector<Main_Menu> main_menu(4);

    /*-----------Titles-------*/

    //Left Panel
    int left_main_x_start{0}, left_main_y_start{0}, left_main_height, left_sub_x_start{0}, left_sub_y_start{0};

    //Mid Panel
    int mid_x_start{0}, mid_y_start{0}, mid_y_end{0}, mid_y;
    //Mid Panel

    int right_x_start{0}, right_y_start{0};

    //Clock over Mid Panel
    int clock_y_start{0}, clock_x_start{0};

    /*--------Transition---------*/

    const int main_menu_delay_duration{300}, sub_menu_delay_duration{250}, sub_menu_max_display{5};

    /*-------------------Reading from file-------------*/

    (main_menu.at(0)).get_data_from_file();
    (main_menu.at(1)).get_data_from_file();
    (main_menu.at(2)).get_data_from_file();
    (main_menu.at(3)).get_data_from_file();

    // //temporary code---------------------------------- experimental purpose
    // {

    //     Side_Menu t1, t2, t3, t4, t5, t6, t7, t8;
    //     t1.set_title("take breakfast");
    //     t1.add_content("taken");

    //     t2.set_title("take lunch");
    //     t2.add_content("nope");

    //     t3.set_title("take breakfast");
    //     t3.add_content("taken");

    //     t4.set_title("take lunch");
    //     t4.add_content("nope");

    //     t5.set_title("take lunch");
    //     t5.add_content("nope");

    //     t6.set_title("take lunch");
    //     t6.add_content("nope");

    //     t7.set_title("take lunch");
    //     t7.add_content("nope");

    //     t8.set_title("take lunch");
    //     t8.add_content("nope");

    //     Main_Menu temp, temp2, temp3;
    //     (main_menu.at(0)).add_content(t1);
    //     (main_menu.at(0)).add_content(t2);
    //     (main_menu.at(0)).add_content(t3);
    //     (main_menu.at(0)).add_content(t4);
    //     (main_menu.at(0)).add_content(t5);
    //     (main_menu.at(0)).add_content(t6);
    //     (main_menu.at(0)).add_content(t7);
    //     (main_menu.at(0)).add_content(t8);

    //     (main_menu.at(1)).add_content(t1);
    //     (main_menu.at(1)).add_content(t2);
    //     (main_menu.at(1)).add_content(t3);
    //     (main_menu.at(1)).add_content(t4);
    //     (main_menu.at(1)).add_content(t4);
    //     temp2.add_content(t2);

    //     (main_menu.at(2)).add_content(t2);
    //     (main_menu.at(2)).add_content(t3);
    //     (main_menu.at(2)).add_content(t4);
    //     (main_menu.at(2)).add_content(t4);
    // }

    // main_menu.at(0).add_data_to_file();
    // main_menu.at(1).add_data_to_file();
    // main_menu.at(2).add_data_to_file();
    // main_menu.at(3).add_data_to_file();

    // std::this_thread::sleep_for(std::chrono::seconds(5));

    /*-------------Key-------------*/

    char key, temp_key{'\0'};

    /*-------------Console-------------*/

    int console_width_temp, console_height_temp;

    /*-------------Main Menu-------------*/

    int main_line{-1}, main_line_2{0};
    bool main_menu_status{true}, main_menu_delay_status{true};

    /*-------------Sub Menu-------------*/

    int sub_line{-1}, sub_line_2{0}, sub_display_line{0};
    bool sub_menu_status{false}, sub_menu_delay_status{true}, sub_menu_add_content_status{false};

    /*-------------Clock, Date & Mid Panel-------------*/

    bool date_separator_display{true}, time_update{false};
    struct tm time_now;
    int time_now_min{0};

    /*-------------Others-------------*/

    int delay_temp;
    bool display_chk{true};
    COORD console_cursor{0, 0}, temp_main_menu_cordinator{0, 0}, temp_cord{0}, temp_main_cord{0};

    //Welcome Screen

    set_console_size(405, 270);
    get_console_size(console_width, console_height);
    set_font_size(21, 44.125, 800);
    console_cursor.X = (console_width * .43);
    console_cursor.Y = (console_height * .45);
    set_console_cursor(console_cursor);
    SetConsoleTextAttribute(color, 11);
    string temp_welcome{"Welcome"};
    for (size_t i{0}; i < temp_welcome.length(); i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        console_cursor_status(false);
        cout << temp_welcome.at(i);
    }
    cout << " ";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    for (size_t i{0}; i < temp_welcome.length(); i++)
    {
        cout << "\b\b ";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    set_font_size(9, 19.125, 600);
    console_width = 1100;
    console_height = 650;
    set_console_size(console_width, console_height);
    console_width = 0;
    console_height = 0;
    console_cursor_status(false);
    while (1)
    {
        //Get Key

        key = '\0';

        if (temp_key != '\0')
        {
            key = temp_key;
            temp_key = '\0';
        }

        if (_kbhit())
            key = _getch();

        /*-------------------------------------
                Console Size & Initialization
        --------------------------------------*/

        get_console_size(console_width, console_height);
        if (console_width != console_width_temp || console_height != console_height_temp)
        {
            /*-------------Left Panel------------*/

            //Main Menu
            left_main_x_start = (console_width * 5) / 100;
            left_main_y_start = console_height / 5;
            left_main_height = (console_height * 0.75);

            //Sub Menu
            left_sub_x_start = (console_width * 5) / 100 + 4;

            /*-------------Mid Panel------------*/

            //Clock over Mid Panel
            clock_y_start = (console_height * 5) / 100;
            clock_x_start = (console_width * 38) / 100 - 1;

            //Seperator

            mid_x_start = (console_width * 38) / 100 - 2;
            mid_y_start = (console_height * 20) / 100;
            mid_y_end = (console_height * 85) / 100;
            mid_y = mid_y_end - mid_y_start;

            // Right Panel
            right_x_start = (console_width * 45) / 100;
            right_y_start = console_height / 5;

            console_width_temp = console_width;
            console_height_temp = console_height;

            system("cls");
            console_cursor_status(false);

            display_chk = true;
            main_menu_status = true;
            // main_menu_delay_status = true;
            // sub_menu_delay_status = true;
            date_separator_display = true;
        }

        //Down Arrow Key

        if (key == 0x50)
        {
            if (sub_menu_status == true)
            {

            down_arrow_key_sub_menu:

                if (sub_menu_add_content_status == true)
                {
                    sub_line = (main_menu.at(main_line)).get_content_number() - 1;
                    sub_menu_add_content_status = false;
                }
                else
                    sub_line++;

                if (sub_line >= ((main_menu.at(main_line)).get_content_number()))
                    sub_line = 0;

                if (sub_line < floor(sub_menu_max_display / 2.0))
                    sub_display_line = 0;

                else if (sub_line > floor(sub_menu_max_display / 2.0) && sub_line < (main_menu.at(main_line)).get_content_number() - floor(sub_menu_max_display / 2.0))
                    sub_display_line = sub_line - floor(sub_menu_max_display / 2.0);

                else if (sub_line >= (main_menu.at(main_line)).get_content_number() - floor(sub_menu_max_display / 2.0))
                    sub_display_line = (main_menu.at(main_line)).get_content_number() - sub_menu_max_display;

                // main_menu_status = true;
            }

            else if (main_menu_status == true)
            {
                main_line++;
                if (main_line >= main_menu.size())
                    main_line = 0;
            }
            display_chk = true;
        }

        //Up Arrow Key

        else if (key == 0x48)
        {
            if (sub_menu_status == true)
            {
                sub_line--;
                if (sub_line < 0)
                    sub_line = (main_menu.at(main_line)).get_content_number() - 1;

                if (sub_line <= (main_menu.at(main_line)).get_content_number() - ceil(sub_menu_max_display / 2.0) && sub_line >= sub_menu_max_display / 2)
                {
                    sub_display_line = sub_line - floor(sub_menu_max_display / 2);
                    if (sub_display_line < 0)
                        sub_display_line = (main_menu.at(main_line)).get_content_number() + sub_line - sub_menu_max_display / 2;
                }
                else if (sub_line > floor(sub_menu_max_display / 2.0))
                {
                    sub_display_line = (main_menu.at(main_line)).get_content_number() - sub_menu_max_display;
                    if (sub_display_line < 0)
                        sub_display_line = 0;
                }

                main_menu_status = true;
            }

            else if (main_menu_status == true)
            {
                main_line--;
                if (main_line < 0)
                    main_line = main_menu.size() - 1;
                main_menu_status = true;
            }
            display_chk = true;
        }

        //Enter Key

        if (key == 13)
        {
            if (sub_menu_status == true)
            {
                if (sub_line == 0)
                    sub_menu_add_content_status = true;
                else
                    (((main_menu).at(main_line)).get_content_address(sub_line))->toggle(); //toggle the status
                display_chk = true;
            }
            else if (main_menu_status == true)
            {
                display_chk = true;
                sub_menu_status = true;
                main_menu_status = true;

                system("cls");
                date_separator_display = true;
            }
        }

        //Escape Key

        if (key == 27)
        {

        exit_sub_menu:

            if (sub_menu_status == true)
            {
                sub_menu_status = false;

                display_chk = true;
                main_menu_status = true;
                sub_menu_delay_status = true;

                sub_line = -1;
                sub_line_2 = 0;
                sub_display_line = 0;

                system("cls");
                date_separator_display = true;
            }

            else if (main_menu_status == true)
            {
                main_menu.at(0).add_data_to_file();
                main_menu.at(1).add_data_to_file();
                main_menu.at(2).add_data_to_file();
                main_menu.at(3).add_data_to_file();

                break;
            }
        }

        /*----------------------
                Clock
        ----------------------*/
        get_local_time(time_now);
        if (time_now.tm_min != time_now_min)
        {
            time_update = true;
            goto time_print;

        get_time:

            time_update = false;
            time_now_min = time_now.tm_min;
        }

        if (display_chk == true)
        {
            /*--------------------------
                    Mid Section
            --------------------------*/

            if (date_separator_display == true)
            {

                /*---------------- Clock over Mid Panel---------------*/

            time_print:

                string time_str;
                get_time_now(time_str); //geting time now
                SetConsoleTextAttribute(color, 9);
                console_cursor.X = clock_x_start - (time_str.length() / 2);
                console_cursor.Y = clock_y_start;
                set_console_cursor(console_cursor);
                cout << time_str;

                if (time_update == true)
                    goto get_time;

                get_date_now(time_str); //getting date now
                console_cursor.X = clock_x_start - (time_str.length() / 2);
                console_cursor.Y += 1;
                set_console_cursor(console_cursor);
                cout << time_str;

                /*----------------Separator---------------*/

                SetConsoleTextAttribute(color, 15);
                for (size_t i{0}; i < mid_y; i++)
                {
                    console_cursor.X = mid_x_start;
                    console_cursor.Y = mid_y_start + i;
                    set_console_cursor(console_cursor);
                    char border_char = char(179);
                    SetConsoleTextAttribute(color, 14);
                    if (i >= (mid_y * 20) / 100 && i <= (mid_y * 80) / 100)
                        cout << border_char;
                    else
                        cout << " ";
                    cout << border_char;
                    if (i >= (mid_y * 20) / 100 && i <= (mid_y * 80) / 100)
                        cout << border_char;

                    cout << endl;
                    SetConsoleTextAttribute(color, 15);
                }
            }
            date_separator_display = false;

            /*-----------------------------------------
                            Left Panel
            -----------------------------------------*/

            /*-----------------Main Panel-----------*/

            if (main_menu_status == true)
            {
                console_cursor.X = left_main_x_start;
                console_cursor.Y = left_main_y_start;

                (main_line_2 != main_line) ? delay_temp = main_menu_delay_duration : delay_temp = 0;

                int temp_height{0}, temp_size{0};

                if (sub_menu_status == true)
                {
                    (sub_menu_max_display <= (main_menu.at(main_line)).get_content_number())
                        ? temp_size = sub_menu_max_display * 2 + 1
                        : temp_size = (main_menu.at(main_line)).get_content_number() * 2 + 1;
                    temp_height = left_main_height - temp_size;
                }
                else
                    temp_height = left_main_height;

                size_t temp_height_space{temp_height / (main_menu.size())};

                for (size_t i{0}; i < main_menu.size(); i++)
                {
                    set_console_cursor(console_cursor);

                    if (sub_menu_status == true && i == main_line)
                    {
                        temp_main_menu_cordinator = console_cursor;
                        console_cursor.Y += temp_size;
                    }

                    temp_main_cord = console_cursor;
                    (main_line == i) ? SetConsoleTextAttribute(color, 12) : SetConsoleTextAttribute(color, 11);

                    if (main_menu_delay_status == true)
                    {
                        char temp_char = delay_print((main_menu.at(i)).get_title(), delay_temp);
                        if (temp_char != '\0')
                        {
                            delay_temp = 0;
                            temp_key = temp_char;
                        }
                    }

                    else
                    {
                        if (sub_menu_status == false && main_line == i)
                            temp_cord = console_cursor;
                        else
                            cout << (main_menu.at(i)).get_title() << endl;

                        if (sub_menu_status == false && i == main_menu.size() - 1)
                        {
                            SetConsoleTextAttribute(color, 6);
                            set_console_cursor(temp_cord);
                            cout << string(mid_x_start - left_sub_x_start, ' ');

                            set_console_cursor(temp_cord);
                            temp_key = delay_print((main_menu.at(main_line)).get_title(), delay_temp);
                        }

                        //Printing Main Menu Descrption

                        if (sub_menu_status != true)
                        {
                            console_cursor.X = right_x_start + ((console_width - right_x_start) * .50) - (((main_menu).at(main_line)).get_description().length() / 2 + 1);
                            console_cursor.Y = right_y_start + left_main_height * .35;

                            set_console_cursor(console_cursor);
                            SetConsoleTextAttribute(color, 15);

                            cout << string(main_menu.at(main_line).get_highest_main_description_length() / 2, '\b')
                                 << string(main_menu.at(main_line).get_highest_main_description_length() / 2, ' ')
                                 << ((main_menu).at(main_line)).get_description()
                                 << string(main_menu.at(main_line).get_highest_main_description_length() / 2, ' ')
                                 << endl;
                        }
                    }

                    console_cursor = temp_main_cord;
                    console_cursor.Y += temp_height_space;
                }
            }

            main_line_2 = main_line;

            main_menu_delay_status = false;

            /*-----------Sub Panel-------------*/

            if (sub_menu_status == true)
            {

                main_menu_status == false; //Stoping Main Menu printing

                console_cursor = temp_main_menu_cordinator;
                console_cursor.X = (console_width * 5) / 100 + 4;

                (sub_line_2 != sub_line) ? delay_temp = sub_menu_delay_duration : delay_temp = 0;

                int temp_size{0};

                (sub_menu_max_display <= (main_menu.at(main_line)).get_content_number())
                    ? temp_size = sub_menu_max_display
                    : temp_size = (main_menu.at(main_line)).get_content_number();

                int temp_sub_line = sub_display_line;

                for (size_t i{0}; i < temp_size; i++)
                {
                    console_cursor.Y += 2;
                    set_console_cursor(console_cursor);
                    COORD cord{console_cursor};
                    SetConsoleTextAttribute(color, 15);

                    if (sub_menu_delay_status == true)
                    {
                        char temp_char{};
                        if (i == 0)
                        {
                            SetConsoleTextAttribute(color, 8);
                            cout << "   ";
                            temp_char = delay_print(((main_menu.at(main_line)).get_content(temp_sub_line)).get_title(), delay_temp);
                        }
                        else
                            temp_char = delay_print(to_string(((main_menu.at(main_line)).get_content(temp_sub_line)).get_title_serial()) + ". " + ((main_menu.at(main_line)).get_content(temp_sub_line)).get_title(), delay_temp);

                        if (temp_char != '\0')
                        {
                            delay_temp = 0;
                            temp_key = temp_char;
                        }
                    }

                    else
                    {
                        if (sub_line == temp_sub_line)
                            temp_cord = console_cursor;
                        else
                        {
                            if (temp_sub_line == 0)
                            {
                                SetConsoleTextAttribute(color, 8);
                                cout << "   ";
                            }
                            else
                                cout << ((main_menu.at(main_line)).get_content(temp_sub_line)).get_title_serial() << ". ";

                            cout << ((main_menu.at(main_line)).get_content(temp_sub_line)).get_title()
                                 << string(mid_x_start - left_sub_x_start - (((main_menu.at(main_line)).get_content(temp_sub_line)).get_title()).length() - 5, ' ')
                                 << endl;
                        }

                        if (i == temp_size - 1)
                        {
                            // // cout << endl;
                            // cout << (((main_menu).at(main_line)).get_content(sub_line)).get_active_status() << "yes" << endl;
                            // cout << (((main_menu).at(main_line)).get_content(sub_line)).get_active_status() << "yes" << endl;

                            //Printing Sub Menu Content

                            console_cursor.X = (console_width * 45) / 100;

                            for (size_t j{0}; j < (((main_menu).at(main_line)).get_content(temp_sub_line)).get_content_size(); j++)
                            {
                                console_cursor.Y = right_y_start + (2 * j);
                                set_console_cursor(console_cursor);

                                ((((main_menu).at(main_line)).get_content(sub_line)).get_active_status() == char(251))
                                    ? SetConsoleTextAttribute(color, 8)
                                    : SetConsoleTextAttribute(color, 15);

                                cout << (((main_menu).at(main_line)).get_content(sub_line)).get_active_status()
                                     << ' ' << (((main_menu).at(main_line)).get_content(sub_line)).get_content(j)
                                     << string((((main_menu).at(main_line)).get_content(sub_line)).get_highest_length() - ((((main_menu).at(main_line)).get_content(temp_sub_line)).get_content(j)).length(), ' ') << endl;
                            }

                            //Delay Printing Sub Menu

                            SetConsoleTextAttribute(color, 6);
                            set_console_cursor(temp_cord);
                            cout << string(mid_x_start - left_sub_x_start, ' ');
                            set_console_cursor(temp_cord);

                            if (sub_line == 0)
                                temp_key = delay_print("   " + ((main_menu.at(main_line)).get_content(sub_line)).get_title(), delay_temp);
                            else
                                temp_key = delay_print(to_string(((main_menu.at(main_line)).get_content(sub_line)).get_title_serial()) + ". " + ((main_menu.at(main_line)).get_content(sub_line)).get_title(), delay_temp);
                        }
                    }

                    console_cursor = cord;
                    if (++temp_sub_line >= (main_menu.at(main_line)).get_content_number())
                        temp_sub_line = 0;
                }
                sub_line_2 = sub_line;
                sub_menu_delay_status = false;

                if ((main_menu.at(main_line)).get_content_number() == 0)
                    goto exit_sub_menu;
            }

            display_chk = false;

            if (sub_menu_add_content_status == true)
            {
                string str;
                Side_Menu temp;

                console_cursor = temp_main_menu_cordinator;
                console_cursor.X = (console_width * 5) / 100 + 4;
                console_cursor.Y += 2;
                set_console_cursor(console_cursor);
                cout << string(mid_x_start - left_sub_x_start, ' ');

                console_cursor = temp_main_menu_cordinator;
                console_cursor.X = (console_width * 5) / 100 + 4 + 3;
                console_cursor.Y += 2;
                set_console_cursor(console_cursor);
                SetConsoleTextAttribute(color, 15);
                console_cursor_status(true);
                getline(cin, str);

                console_cursor = temp_main_menu_cordinator;
                console_cursor.X = (console_width * 5) / 100 + 4 + 3;
                console_cursor.Y += 2;
                set_console_cursor(console_cursor);
                SetConsoleTextAttribute(color, 12);
                cout << str << endl;
                temp.set_title(str);

                console_cursor.X = (console_width * 45) / 100;
                console_cursor.Y = right_y_start;
                set_console_cursor(console_cursor);
                SetConsoleTextAttribute(color, 15);
                cout << char(254) << string(((main_menu.at(main_line)).get_content(0)).get_content(0).length() + 2, ' ') << endl;
                console_cursor.X = (console_width * 45) / 100 + 3;
                console_cursor.Y = right_y_start;
                set_console_cursor(console_cursor);
                getline(cin, str);
                console_cursor_status(false);
                temp.add_content(str);

                (main_menu.at(main_line)).add_content(temp);

                display_chk = true;
                key = '\0';

                goto down_arrow_key_sub_menu;
            }
        }
    }

    return 0;
}