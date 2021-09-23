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

    /*---------------------------------------------------------------------------------*
    *-------------------------------------Declarations---------------------------------*
    *---------------------------------------------------------------------------------*/

    /*-----------Menus-------*/

    vector<Main_Menu> main_menu(4);

    //Left Panel
    int left_main_x_start{0}, left_main_y_start{0}, left_main_height, left_sub_x_start{0}, left_sub_y_start{0};

    //Mid Panel

    int mid_x_start{0}, mid_y_start{0}, mid_y_end{0}, mid_height;

    //Right Panel

    int right_x_start{0}, right_y_start{0};

    //Clock over Mid Panel

    int clock_y_start{0}, clock_x_start{0};

    /*--------Transition---------*/

    const int main_menu_delay_duration{300}, sub_menu_delay_duration{250}, sub_menu_title_max_display{5}, sub_menu_content_max_display{9};

    /*-------------main_key-------------*/

    char main_key{'\0'}, temp_key{'\0'};

    /*-------------Console-------------*/

    int console_width{0}, console_height{0}, console_width_temp{0}, console_height_temp{0};
    bool console_size_change_status{false};

    /*-------------Main Menu-------------*/

    int main_menu_title_line{-1}, main_menu_title_line_2{0};
    bool main_menu_title_display_status{true}, main_menu_title_delay_status{true};

    /*-------------Sub Menu-------------*/

    int sub_menu_title_line{-1}, sub_menu_title_line_2{0}, sub_menu_content_line{0},
        sub_menu_title_display_line{0}, sub_menu_content_display_line{0}, temp_sub_menu_content_display_line{0},
        sub_menu_adding_status{0}, sub_menu_content_being_added{0}, temp_sub_menu_content_max_display;

    bool sub_menu_title_display_status{false}, sub_menu_title_delay_status{true}, sub_menu_add_todo_status{false}, sub_menu_add_diary_status{false},
        sub_menu_add_reminder_status{false}, sub_menu_string_print_status{false}, sub_menu_content_display_status{false}, sub_menu_add_first_content{true},
        sub_menu_add_content_only{false};

    char content_main_key{'\0'};
    COORD sub_menu_add_content_cord{0}, sub_menu_add_content_cord_2{0};
    string sub_menu_string;
    Side_Menu temp_side_menu_content;
    size_t sub_menu_time_now{0};

    // bool sub_menu_todo_title_setter_status{false}, sub_menu_todo_content_setter_status{false}, sub_menu_diary_title_setter_status{false}, sub_menu_diary_contetnt_setter_status { false };

    /*-------------Clock, Date & Mid Panel-------------*/

    bool date_and_separator_display_stauts{true}, time_update{false};
    struct tm time_now;
    int time_now_min{0};

    /*-------------Welcome Screen-------------*/

    size_t welcome_printing_start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    const int welcome_printing_duration{1000};
    int temp_welcome_printing_duration{0};
    string welcome_text{"Welcome"};

    /*-------------Others-------------*/

    int delay_temp;
    bool display_status{true};
    COORD console_cursor{0, 0}, temp_main_menu_cordinator{0, 0}, temp_main_cord{0};

    /*---------------------------------------------------------------------------------*
    *---------------------------------------Methods------------------------------------*
    *---------------------------------------------------------------------------------*/

    /*-------------------Writing to file for exterimental purposes-------------*/

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

    /*-------------------Reading from file-------------*/

    (main_menu.at(0)).get_data_from_file();
    (main_menu.at(1)).get_data_from_file();
    (main_menu.at(2)).get_data_from_file();
    (main_menu.at(3)).get_data_from_file();

    /*-------------Welcome Screen-------------*/

    system("cls");

    set_console_size(405, 270);
    get_console_size(console_width, console_height);
    set_font_size(21, 44.125, 800);

    console_cursor.X = (console_width * .43);
    console_cursor.Y = (console_height * .45);
    set_console_cursor(console_cursor);

    temp_welcome_printing_duration = (welcome_printing_duration - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() + welcome_printing_start) / welcome_text.length();

    for (size_t i{0}; i < welcome_text.length(); i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(temp_welcome_printing_duration));
        console_cursor_status(false);

        SetConsoleTextAttribute(color, 11);
        cout << "\b\b" << welcome_text.at(i) << " ";

        SetConsoleTextAttribute(color, 8);
        // cout << char(175);
        cout << ">";
    }
    cout << " ";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    for (size_t i{0}; i < welcome_text.length(); i++)
    {
        cout << "\b\b\b\b "
             << "<"
             << " ";
        std::this_thread::sleep_for(std::chrono::milliseconds(temp_welcome_printing_duration * 7 / 10));
    }

    /*-------------Main Interface Initialization-------------*/

    set_font_size(9, 19.125, 600);
    console_width = 1100;
    console_height = 650;
    set_console_size(console_width, console_height);
    console_width = 0;
    console_height = 0;
    console_cursor_status(false);

    /*------------------Odyssey--------------*/

    while (1)
    {
        //Get main_key

        main_key = '\0';

        if (temp_key != '\0')
        {
            main_key = temp_key;
            temp_key = '\0';
        }

        if (_kbhit())
            main_key = _getch();

        /*-------------------------------------
                Console Size & Initialization
        --------------------------------------*/

    console_size_and_initialization:

        console_size_change_status = false;

        get_console_size(console_width, console_height);

        if (console_width != console_width_temp || console_height != console_height_temp)
        {

            if (console_width < 87 || console_height < 27)
            {
                set_console_size(870, 570);
                get_console_size(console_width, console_height);
            }

            console_size_change_status = true;
            sub_menu_string_print_status = true;

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
            mid_height = mid_y_end - mid_y_start;

            // Right Panel
            right_x_start = (console_width * 45) / 100;
            right_y_start = console_height / 5;

            console_width_temp = console_width;
            console_height_temp = console_height;

            system("cls");
            console_cursor_status(false);

            display_status = true;
            // main_menu_title_display_status = true;
            // sub_menu_title_display_status = true;
            main_menu_title_delay_status = main_menu_title_line >= 0 ? false : true;
            sub_menu_title_delay_status = sub_menu_title_line >= 0 ? false : true;
            date_and_separator_display_stauts = true;
        }

        /*----------------------
                Clock
        ----------------------*/

        // console_size_and_initialization:
        console_cursor_status(false);

        get_local_time(time_now);
        if (time_now.tm_min != time_now_min)
        {
            time_update = true;
            goto display_clock;

        update_clock_values:

            time_update = false;
            time_now_min = time_now.tm_min;
        }

        if (!console_size_change_status)
        {

            switch (sub_menu_adding_status)
            {
            case 1:
                sub_menu_adding_status = 0;
                goto to_do_title_setter;
                break;
            case 2:
                sub_menu_adding_status = 0;
                goto to_do_content_setter;
                break;
                // case 1:
                //     goto to_do_title_setter;
                //     break;
                // case 1:
                //     goto to_do_title_setter;
                //     break;

            default:
                break;
            }
        }

        /*----------------------------Down Arrow main_key----------------------------*/

        if (main_key == 0x50)
        {
            if (sub_menu_content_display_status)
            {
                sub_menu_content_line++;
                if (sub_menu_content_line >= ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size())
                    sub_menu_content_line = 0;

                if (sub_menu_content_line <= sub_menu_content_max_display / 2)
                    sub_menu_content_display_line = 0;
                else if (sub_menu_content_line >= ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() - sub_menu_content_max_display / 2)
                {
                    if (((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() >= sub_menu_content_max_display)
                        sub_menu_content_display_line = ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() - sub_menu_content_max_display;

                    if (((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() < sub_menu_content_max_display)
                        sub_menu_content_display_line = 0;
                }
                else
                    sub_menu_content_display_line = sub_menu_content_line - sub_menu_content_max_display / 2;
            }

            else if (sub_menu_title_display_status)
            {
                sub_menu_title_line++;

            down_arrow_main_key_sub_menu:

                if (sub_menu_title_line >= ((main_menu.at(main_menu_title_line)).get_content_number()))
                    sub_menu_title_line = 0;

                if (sub_menu_title_line <= sub_menu_title_max_display / 2)
                    sub_menu_title_display_line = 0;
                else if (sub_menu_title_line >= (main_menu.at(main_menu_title_line)).get_content_number() - sub_menu_title_max_display / 2)
                {
                    if ((main_menu.at(main_menu_title_line)).get_content_number() >= sub_menu_title_max_display)
                        sub_menu_title_display_line = (main_menu.at(main_menu_title_line)).get_content_number() - sub_menu_title_max_display;

                    if ((main_menu.at(main_menu_title_line)).get_content_number() < sub_menu_title_max_display)
                        sub_menu_title_display_line = 0;
                }
                else
                    sub_menu_title_display_line = sub_menu_title_line - sub_menu_title_max_display / 2;
            }

            else if (main_menu_title_display_status)
            {
                main_menu_title_line++;
                if (main_menu_title_line >= main_menu.size())
                    main_menu_title_line = 0;
            }
            display_status = true;
        }

        /*----------------------------Up Arrow main_key----------------------------*/

        else if (main_key == 0x48)
        {
            if (sub_menu_content_display_status)
            {
                sub_menu_content_line--;
                if (sub_menu_content_line < 0)
                    sub_menu_content_line = ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() - 1;

                if (sub_menu_content_line <= sub_menu_content_max_display / 2)
                    sub_menu_content_display_line = 0;
                else if (sub_menu_content_line >= ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() - sub_menu_content_max_display / 2)
                {
                    if (((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() >= sub_menu_content_max_display)
                        sub_menu_content_display_line = ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() - sub_menu_content_max_display;

                    if (((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() < sub_menu_content_max_display)
                        sub_menu_content_display_line = 0;
                }
                else
                    sub_menu_content_display_line = sub_menu_content_line - sub_menu_content_max_display / 2;

                // main_menu_title_display_status = true;
            }

            else if (sub_menu_title_display_status)
            {
                sub_menu_title_line--;
                if (sub_menu_title_line < 0)
                    sub_menu_title_line = (main_menu.at(main_menu_title_line)).get_content_number() - 1;

                if (sub_menu_title_line <= sub_menu_title_max_display / 2)
                    sub_menu_title_display_line = 0;
                else if (sub_menu_title_line >= (main_menu.at(main_menu_title_line)).get_content_number() - sub_menu_title_max_display / 2)
                {
                    if ((main_menu.at(main_menu_title_line)).get_content_number() >= sub_menu_title_max_display)
                        sub_menu_title_display_line = (main_menu.at(main_menu_title_line)).get_content_number() - sub_menu_title_max_display;

                    if ((main_menu.at(main_menu_title_line)).get_content_number() < sub_menu_title_max_display)
                        sub_menu_title_display_line = 0;
                }
                else
                    sub_menu_title_display_line = sub_menu_title_line - sub_menu_title_max_display / 2;

                // main_menu_title_display_status = true;
            }

            else if (main_menu_title_display_status)
            {
                main_menu_title_line--;
                if (main_menu_title_line < 0)
                    main_menu_title_line = main_menu.size() - 1;
                main_menu_title_display_status = true;
            }
            display_status = true;
        }

        /*-----------------------------Enter key-----------------------------*/

        if (main_key == 13)
        {
            if (sub_menu_content_display_status)
            {
                if (sub_menu_content_line == 0)
                {
                    sub_menu_add_content_only = true;
                    goto todo_add_content;
                }
                else
                {
                    (((main_menu).at(main_menu_title_line)).get_content_reference(sub_menu_title_line))->toggle(sub_menu_content_line); //toggle the status
                    display_status = true;
                }
            }

            else if (sub_menu_title_display_status)
            {
                if (sub_menu_title_line == 0)
                {
                    switch (main_menu_title_line)
                    {
                    case 0:
                        sub_menu_add_todo_status = true;
                        break;
                    case 1:
                        sub_menu_add_reminder_status = true;
                        break;
                    case 2:
                        sub_menu_add_diary_status = true;
                        break;

                    default:
                        break;
                    }
                }
                else
                    sub_menu_content_display_status = true;

                display_status = true;
            }

            else if (main_menu_title_display_status)
            {
                display_status = true;
                sub_menu_title_display_status = true;

                system("cls");
                date_and_separator_display_stauts = true;
            }
        }

        /*-----------------------------Escape key-----------------------------*/

        if (main_key == 27)
        {
        exit_sub_menu:

            if (sub_menu_content_display_status)
            {
                sub_menu_content_display_status = false;

                sub_menu_title_display_status = true;
                display_status = true;

                sub_menu_content_line = 0;

                // system("cls");
                date_and_separator_display_stauts = true;
                sub_menu_add_first_content = true;
            }

            else if (sub_menu_title_display_status)
            {
                sub_menu_title_display_status = false;

                display_status = true;
                main_menu_title_display_status = true;
                sub_menu_title_delay_status = true;

                sub_menu_title_line = -1;
                sub_menu_title_line_2 = 0;
                sub_menu_title_display_line = 0;

                system("cls");
                date_and_separator_display_stauts = true;
            }

            else if (main_menu_title_display_status)
            {
                main_menu.at(0).add_data_to_file();
                main_menu.at(1).add_data_to_file();
                main_menu.at(2).add_data_to_file();
                main_menu.at(3).add_data_to_file();

                break;
            }
        }

        /*--------------------------
                Display Status
         --------------------------*/

        if (display_status)
        {
            /*--------------------------
                    Mid Section
            --------------------------*/

            if (date_and_separator_display_stauts)
            {

                /*---------------- Clock over Mid Panel---------------*/

            display_clock:

                string time_str;
                get_time_now(time_str); //geting time now
                SetConsoleTextAttribute(color, 9);
                console_cursor.X = clock_x_start - (time_str.length() / 2);
                console_cursor.Y = clock_y_start;
                set_console_cursor(console_cursor);
                cout << time_str;

                if (time_update)
                    goto update_clock_values;

                get_date_now(time_str); //getting date now
                console_cursor.X = clock_x_start - (time_str.length() / 2);
                console_cursor.Y += 1;
                set_console_cursor(console_cursor);
                cout << time_str;

                /*----------------Separator---------------*/

                SetConsoleTextAttribute(color, 15);
                for (size_t i{0}; i < mid_height; i++)
                {
                    console_cursor.X = mid_x_start;
                    console_cursor.Y = mid_y_start + i;
                    set_console_cursor(console_cursor);
                    char border_char = char(179);
                    SetConsoleTextAttribute(color, 14);
                    if (i >= (mid_height * 20) / 100 && i <= (mid_height * 80) / 100)
                        cout << border_char;
                    else
                        cout << " ";
                    cout << border_char;
                    if (i >= (mid_height * 20) / 100 && i <= (mid_height * 80) / 100)
                        cout << border_char;

                    cout << endl;
                    SetConsoleTextAttribute(color, 15);
                }
            }
            date_and_separator_display_stauts = false;

            /*-----------------------------------------
                            Left Panel
            -----------------------------------------*/

            /*-----------------Main Panel-----------*/

            if (main_menu_title_display_status)
            {
                console_cursor.X = left_main_x_start;
                console_cursor.Y = left_main_y_start;

                (main_menu_title_line_2 != main_menu_title_line) ? delay_temp = main_menu_delay_duration : delay_temp = 0;

                int temp_height{0}, temp_size{0};

                if (sub_menu_title_display_status)
                {
                    (sub_menu_title_max_display <= (main_menu.at(main_menu_title_line)).get_content_number())
                        ? temp_size = sub_menu_title_max_display * 2 + 1
                        : temp_size = (main_menu.at(main_menu_title_line)).get_content_number() * 2 + 1;
                    temp_height = left_main_height - temp_size;
                }
                else
                    temp_height = left_main_height;

                size_t temp_height_space{temp_height / (main_menu.size())};

                for (size_t i{0}; i < main_menu.size(); i++)
                {
                    set_console_cursor(console_cursor);

                    if (i == main_menu_title_line)
                    {
                        temp_main_menu_cordinator = console_cursor;

                        if (sub_menu_title_display_status)
                            console_cursor.Y += temp_size;
                    }

                    temp_main_cord = console_cursor;
                    (main_menu_title_line == i) ? SetConsoleTextAttribute(color, 12) : SetConsoleTextAttribute(color, 11);

                    if (main_menu_title_delay_status)
                    {
                        main_menu.at(i).set_cordinator(console_cursor);

                        char temp_char = delay_print((main_menu.at(i)).get_title(), delay_temp);
                        if (temp_char != '\0')
                        {
                            delay_temp = 0;
                            temp_key = temp_char;
                        }
                    }

                    else
                    {
                        set_console_cursor((main_menu.at(i)).get_cordinator());
                        cout << string((main_menu.at(i).get_title()).length(), ' ');
                        set_console_cursor(console_cursor);
                        main_menu.at(i).set_cordinator(get_console_cursor());

                        if (sub_menu_title_display_status || main_menu_title_line != i)
                        {
                            if (main_menu_title_line == i)
                                set_console_cursor(temp_main_menu_cordinator);
                            cout << (main_menu.at(i)).get_title() << endl;
                        }

                        if (!sub_menu_title_display_status && i == main_menu.size() - 1)
                        {
                            //Printing Main Menu Descrption

                            console_cursor.X = right_x_start + ((console_width - right_x_start) * .50) - (((main_menu).at(main_menu_title_line)).get_description().length() / 2 + 1);
                            console_cursor.Y = right_y_start + left_main_height * .35;

                            set_console_cursor(console_cursor);
                            SetConsoleTextAttribute(color, 15);

                            cout << string(main_menu.at(main_menu_title_line).get_highest_main_description_length() / 2, '\b')
                                 << string(main_menu.at(main_menu_title_line).get_highest_main_description_length() / 2, ' ')
                                 << ((main_menu).at(main_menu_title_line)).get_description()
                                 << string(main_menu.at(main_menu_title_line).get_highest_main_description_length() - ((main_menu).at(main_menu_title_line)).get_description().length() / 2, ' ')
                                 << endl;

                            //Printing Delay Main Menu Title

                            SetConsoleTextAttribute(color, 6);
                            set_console_cursor(temp_main_menu_cordinator);
                            cout << string(mid_x_start - left_sub_x_start, ' ');

                            set_console_cursor(temp_main_menu_cordinator);
                            temp_key = delay_print((main_menu.at(main_menu_title_line)).get_title(), delay_temp);
                        }
                    }

                    console_cursor = temp_main_cord;
                    console_cursor.Y += temp_height_space;
                }
            }

            main_menu_title_line_2 = main_menu_title_line;

            main_menu_title_delay_status = false;

            /*-----------Sub Panel-------------*/

            if (sub_menu_title_display_status)
            {
                main_menu_title_display_status == false; //Stoping Main Menu printing

                console_cursor = temp_main_menu_cordinator;
                console_cursor.X = (console_width * 5) / 100 + 4;

                (sub_menu_title_line_2 != sub_menu_title_line) ? delay_temp = sub_menu_delay_duration : delay_temp = 0;

                int temp_size{0};

                (sub_menu_title_max_display <= (main_menu.at(main_menu_title_line)).get_content_number())
                    ? temp_size = sub_menu_title_max_display
                    : temp_size = (main_menu.at(main_menu_title_line)).get_content_number();

                int temp_sub_menu_title_line = sub_menu_title_display_line;
                COORD temp_cord{0};

                for (size_t i{0}; i < temp_size; i++)
                {
                    console_cursor.Y += 2;
                    set_console_cursor(console_cursor);
                    (sub_menu_title_line == temp_sub_menu_title_line)
                        ? SetConsoleTextAttribute(color, 12)
                        : SetConsoleTextAttribute(color, 15);

                    if (sub_menu_title_delay_status)
                    {
                        char temp_char{};
                        if (i == 0)
                        {
                            SetConsoleTextAttribute(color, 8);
                            cout << "   ";
                            temp_char = delay_print(((main_menu.at(main_menu_title_line)).get_content(temp_sub_menu_title_line)).get_title(), delay_temp);
                        }
                        else
                            temp_char = delay_print(to_string(((main_menu.at(main_menu_title_line)).get_content(temp_sub_menu_title_line)).get_title_serial()) + ". " + ((main_menu.at(main_menu_title_line)).get_content(temp_sub_menu_title_line)).get_title(), delay_temp);

                        if (temp_char != '\0')
                        {
                            delay_temp = 0;
                            temp_key = temp_char;
                        }
                    }

                    else
                    {
                        if (!sub_menu_content_display_status && sub_menu_title_line == temp_sub_menu_title_line)
                            temp_cord = console_cursor;
                        else
                        {
                            if (temp_sub_menu_title_line == 0)
                            {
                                SetConsoleTextAttribute(color, 8);
                                cout << "   ";
                            }
                            else
                                cout << ((main_menu.at(main_menu_title_line)).get_content(temp_sub_menu_title_line)).get_title_serial() << ". ";

                            cout << ((main_menu.at(main_menu_title_line)).get_content(temp_sub_menu_title_line)).get_title()
                                 << string(mid_x_start - left_sub_x_start - (((main_menu.at(main_menu_title_line)).get_content(temp_sub_menu_title_line)).get_title()).length() - 5, ' ')
                                 << endl;
                        }

                        if (!sub_menu_content_display_status && i == temp_size - 1)
                        {
                            //Printing Sub Menu Content

                            console_cursor.X = right_x_start;

                            int temp_highest_content_number =
                                ((((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line - 1 < 0 ? ((main_menu).at(main_menu_title_line)).get_content_number() + sub_menu_title_line - 1 : sub_menu_title_line - 1)).get_content_size() >
                                 (((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line + 1 >= ((main_menu).at(main_menu_title_line)).get_content_number() ? 0 : sub_menu_title_line + 1)).get_content_size())
                                    ? ((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line - 1 < 0 ? ((main_menu).at(main_menu_title_line)).get_content_number() + sub_menu_title_line - 1 : sub_menu_title_line - 1).get_content_size()
                                    : ((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line + 1 >= ((main_menu).at(main_menu_title_line)).get_content_number() ? 0 : sub_menu_title_line + 1).get_content_size();

                            for (size_t j{0}; j <= temp_highest_content_number; j++)
                            {
                                console_cursor.Y = right_y_start + (2 * j);

                                set_console_cursor(console_cursor);
                                cout << string(console_width - right_x_start, ' ') << endl;
                            }

                            console_cursor.X = right_x_start;

                            int temp_sub_menu_title_max_display = ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() < sub_menu_content_max_display
                                                                      ? ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size()
                                                                      : sub_menu_content_max_display;

                            (((main_menu).at(main_menu_title_line)).get_content_reference(sub_menu_title_line))->sort();

                            for (size_t j{0}; j < temp_sub_menu_title_max_display; j++)
                            {
                                console_cursor.Y = right_y_start + (2 * j);
                                set_console_cursor(console_cursor);

                                ((((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_active_status(j) == char(251))
                                    ? SetConsoleTextAttribute(color, 8)
                                    : SetConsoleTextAttribute(color, 15);

                                cout << (((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_active_status(j)
                                     << ' ' << (((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(j);
                            }

                            //Delay Printing Sub Menu

                            console_cursor.X = 0;
                            console_cursor.Y = 0;
                            set_console_cursor(console_cursor);

                            SetConsoleTextAttribute(color, 6);
                            set_console_cursor(temp_cord);
                            cout << string(mid_x_start - left_sub_x_start, ' ');
                            set_console_cursor(temp_cord);

                            if (sub_menu_title_line == 0)
                                temp_key = delay_print("   " + ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_title(), delay_temp);
                            else
                                temp_key = delay_print(to_string(((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_title_serial()) + ". " + ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_title(), delay_temp);

                            console_cursor = temp_cord;
                        }
                    }

                    if (++temp_sub_menu_title_line >= (main_menu.at(main_menu_title_line)).get_content_number())
                        temp_sub_menu_title_line = 0;
                }
                sub_menu_title_line_2 = sub_menu_title_line;
                sub_menu_title_delay_status = false;

                if ((main_menu.at(main_menu_title_line)).get_content_number() == 0)
                    goto exit_sub_menu;
            }

            /*------------------------------------Sub Menu Content Display--------------------------------------*/

            if (sub_menu_content_display_status)
            {
                main_menu_title_display_status == false; //Stoping Main Menu printing
                sub_menu_title_display_status == false;  //Stoping Sub Menu title printing

                int temp_sub_menu_content_max_display =
                    ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() < sub_menu_content_max_display
                        ? ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size()
                        : sub_menu_content_max_display;

                int temp_sub_menu_content_display_line = sub_menu_content_display_line;

                ((main_menu.at(main_menu_title_line)).get_content_reference(sub_menu_title_line))->sort();

                for (size_t i{0}; i < temp_sub_menu_content_max_display; i++)
                {
                    console_cursor.X = right_x_start;
                    console_cursor.Y = right_y_start + (2 * i);
                    set_console_cursor(console_cursor);

                    if (temp_sub_menu_content_display_line == sub_menu_content_line)
                        SetConsoleTextAttribute(color, 6);
                    else if (((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_active_status(temp_sub_menu_content_display_line) == char(251))
                        SetConsoleTextAttribute(color, 8);
                    else
                        SetConsoleTextAttribute(color, 15);

                    cout << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_active_status(temp_sub_menu_content_display_line)
                         << " "
                         << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(temp_sub_menu_content_display_line)
                         << string(console_width - right_x_start - ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(temp_sub_menu_content_display_line).length() - 2, ' ') << endl;

                    if (++temp_sub_menu_content_display_line >= ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size())
                        temp_sub_menu_content_display_line = 0;
                }
            }

            /*-------------------------------------------------------------------
            *-------------------------Add to To Do List------------------
            *-------------------------------------------------------------------*/

            if (sub_menu_add_todo_status)
            {
                sub_menu_title_display_status = false;
                main_menu_title_display_status = false;

                switch (sub_menu_adding_status)
                {
                case 1:
                    sub_menu_adding_status = 0;
                    goto to_do_title_setter;
                    break;
                case 2:
                    sub_menu_adding_status = 0;
                    goto to_do_content_setter;
                    break;
                    // case 1:
                    //     goto to_do_title_setter;
                    //     break;
                    // case 1:
                    //     goto to_do_title_setter;
                    //     break;

                default:
                    break;
                }

                temp_side_menu_content.reset();

                sub_menu_string_print_status = true;

                sub_menu_time_now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

                console_cursor_status(true);

                {
                    sub_menu_string.clear();

                    while (1)
                    {

                        sub_menu_adding_status = 1;
                        goto console_size_and_initialization;

                    to_do_title_setter:

                        SetConsoleTextAttribute(color, 15);

                        console_cursor.X = (console_width * 5) / 100 + 4 + 3 + sub_menu_string.length();
                        console_cursor.Y = temp_main_menu_cordinator.Y + 2;
                        set_console_cursor(console_cursor);

                        if ((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - sub_menu_time_now) % 1000 >= 500)
                            // cout << char(222);
                            cout << "|";
                        else
                            cout << " ";

                        if (sub_menu_string_print_status)
                        {
                            SetConsoleTextAttribute(color, 15);

                            console_cursor.X = (console_width * 5) / 100 + 4;
                            console_cursor.Y = temp_main_menu_cordinator.Y + 2;
                            set_console_cursor(console_cursor);
                            cout << string(mid_x_start - left_sub_x_start, ' ');

                            console_cursor.X += 3;
                            set_console_cursor(console_cursor);
                            cout << sub_menu_string;

                            sub_menu_string_print_status = false;
                        }

                        content_main_key = '\0';

                        if (_kbhit())
                        {
                            content_main_key = _getch();
                            if (content_main_key >= 32 && content_main_key <= 126)
                            {
                                sub_menu_string += content_main_key;
                                sub_menu_string_print_status = true;
                            }
                            else if (content_main_key == 8 && sub_menu_string.length() > 0)
                            {
                                sub_menu_string.erase(sub_menu_string.begin() + sub_menu_string.length() - 1);
                                sub_menu_string_print_status = true;
                                cout << "\b\b  \b\b";
                            }
                            else if (content_main_key == 13 || content_main_key == 27)
                                break;
                        }
                    }
                }

                sub_menu_content_being_added = 0;

                //If enter main_key if pressed

                if (content_main_key == 13)
                {
                    temp_side_menu_content.set_title(sub_menu_string);

                    //Printing Sub Menu Title for once

                    {
                        console_cursor.X = (console_width * 5) / 100 + 4;
                        console_cursor.Y = temp_main_menu_cordinator.Y + 2;
                        set_console_cursor(console_cursor);
                        cout << string(mid_x_start - left_sub_x_start, ' ');

                        console_cursor.X += 3;
                        set_console_cursor(console_cursor);
                        SetConsoleTextAttribute(color, 12);
                        cout << temp_side_menu_content.get_title() << " ";
                    }

                todo_add_content:

                    sub_menu_string.clear();

                    while (1)
                    {
                        sub_menu_adding_status = 2;
                        goto console_size_and_initialization;

                    to_do_content_setter:

                        temp_sub_menu_content_max_display = sub_menu_content_being_added < sub_menu_content_max_display
                                                                ? sub_menu_content_being_added
                                                                : sub_menu_content_max_display;

                        if (console_size_change_status)
                        {
                            console_cursor.X = (console_width * 5) / 100 + 4;
                            console_cursor.Y = temp_main_menu_cordinator.Y + 2;
                            set_console_cursor(console_cursor);
                            cout << string(mid_x_start - left_sub_x_start, ' ');

                            console_cursor.X += 3;
                            set_console_cursor(console_cursor);
                            SetConsoleTextAttribute(color, 12);
                            cout << temp_side_menu_content.get_title() << " ";

                            SetConsoleTextAttribute(color, 15);

                            if (sub_menu_content_being_added < sub_menu_content_max_display)
                                temp_sub_menu_content_display_line = 0;
                            else
                                temp_sub_menu_content_display_line = sub_menu_content_being_added - sub_menu_content_max_display + 1;

                            for (size_t j{0}; j < temp_sub_menu_content_max_display; j++)
                            {
                                console_cursor.X = right_x_start;
                                console_cursor.Y = right_y_start + j * 2;

                                set_console_cursor(console_cursor);
                                cout << temp_side_menu_content.get_active_status(temp_sub_menu_content_display_line) << " "
                                     << temp_side_menu_content.get_content(temp_sub_menu_content_display_line)
                                     << string(console_width - right_x_start - temp_side_menu_content.get_content(temp_sub_menu_content_display_line).length(), ' ') << endl;

                                temp_sub_menu_content_display_line++;
                            }
                        }

                        SetConsoleTextAttribute(color, 15);

                        console_cursor.X = right_x_start + sub_menu_string.length() + 2;
                        console_cursor.Y = right_y_start;
                        set_console_cursor(console_cursor);

                        if (sub_menu_add_first_content)
                        {
                            SetConsoleTextAttribute(color, 8);
                            cout << "\b\b" << char(175);
                            set_console_cursor(console_cursor);
                            cout << temp_side_menu_content.get_content(temp_sub_menu_content_display_line) << endl;
                            set_console_cursor(console_cursor);
                            cout << '\b';
                            SetConsoleTextAttribute(color, 15);
                        }

                        if ((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - sub_menu_time_now) % 1000 >= 500)
                            cout << "|";
                        else
                            cout << " ";

                        if (sub_menu_string_print_status)
                        {
                            console_cursor.X = right_x_start;
                            console_cursor.Y = right_y_start;
                            set_console_cursor(console_cursor);
                            cout << string(console_width - right_x_start, ' ') << endl;

                            set_console_cursor(console_cursor);
                            cout << temp_side_menu_content.get_active_status(temp_side_menu_content.get_content_size() - 1) << " " << sub_menu_string;

                            sub_menu_string_print_status = false;

                            if (content_main_key == 13)
                                break;
                        }

                        content_main_key = '\0';

                        if (_kbhit())
                        {
                            content_main_key = _getch();
                            if (content_main_key >= 32 && content_main_key <= 126)
                            {
                                sub_menu_string += content_main_key;

                                sub_menu_string_print_status = true;
                                sub_menu_add_first_content = false;
                            }

                            else if (content_main_key == 8)
                            {
                                sub_menu_string.erase(sub_menu_string.begin() + sub_menu_string.length() - 1);
                                cout << "\b\b  \b\b";
                            }

                            else if (content_main_key == 13 && sub_menu_string.length() > 0)
                            {
                                cout << "\b ";

                                sub_menu_content_being_added++;

                                temp_side_menu_content.add_content(sub_menu_string);

                                sub_menu_string_print_status = true;
                            }

                            else if (content_main_key == 27)
                            {
                                console_cursor.X = right_x_start;
                                console_cursor.Y = right_y_start + sub_menu_content_being_added * 2;
                                set_console_cursor(console_cursor);
                                cout << string(console_width - right_x_start, ' ');
                                break;
                            }
                        }
                    }

                    if (sub_menu_add_content_only)
                    {
                        ((main_menu.at(main_menu_title_line)).get_content_reference(sub_menu_title_line))->add_content(sub_menu_string);
                        sub_menu_add_content_only = false;
                    }
                    else
                    {
                        (main_menu.at(main_menu_title_line)).add_content(temp_side_menu_content);
                        sub_menu_title_line = (main_menu.at(main_menu_title_line)).get_content_number() - 1;
                    }
                }
                else
                    sub_menu_title_line = 0;

                console_cursor_status(false);

                display_status = true;
                main_key = '\0';

                sub_menu_add_todo_status = false;
                sub_menu_add_first_content = true;

                main_menu_title_display_status = true;
                sub_menu_title_display_status = true;
                sub_menu_content_display_status = true;

                sub_menu_content_line = 0;

                goto down_arrow_main_key_sub_menu;
            }

            display_status = false;
        }
    }

    return 0;
}
