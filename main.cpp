#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <chrono>
#include "user_function.h"
#include "main_menu.h"
#include "side_menu.h"
using namespace std;

int main()
{
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

    /* -------------------------------------------------------------------------- */
    /*                                Declarations                                */
    /* -------------------------------------------------------------------------- */

    /* ---------------------------------- Menus --------------------------------- */

    vector<Main_Menu> main_menu(4);

    // Left Panel
    int left_main_x_start{0}, left_main_y_start{0}, left_main_height, left_sub_x_start{0}, left_sub_y_start{0};

    // Mid Panel
    int mid_x_start{0}, mid_y_start{0}, mid_y_end{0}, mid_height;

    // Right Panel
    int right_x_start{0}, right_y_start{0}, right_x_width;

    // Clock over Mid Panel
    int clock_y_start{0}, clock_x_start{0};

    /* ------------------------------- Transition/ ------------------------------ */

    const int main_menu_delay_duration{300}, sub_menu_delay_duration{250}, sub_menu_title_max_display{5}, sub_menu_content_max_display{9}, sub_menu_reminder_content_max_display{6};

    /* -------------------------------- main_key -------------------------------- */

    char main_key{'\0'}, temp_key{'\0'};

    /* --------------------------------- Console -------------------------------- */

    int console_width{0}, console_height{0}, console_width_temp{0}, console_height_temp{0};
    bool console_size_change_status{false};

    /* -------------------------------- Main Menu ------------------------------- */

    int main_menu_title_line{-1}, main_menu_title_line_2{0};
    bool main_menu_title_display_status{true}, main_menu_title_delay_status{true};

    /* -------------------------------- Sub Menu -------------------------------- */

    int sub_menu_title_line{-1}, sub_menu_title_line_2{0}, sub_menu_content_line{0},
        sub_menu_title_display_line{0}, sub_menu_content_display_line{0}, temp_sub_menu_content_display_line{0},
        sub_menu_content_being_added{0}, temp_sub_menu_content_max_display{0};

    bool sub_menu_title_display_status{false}, sub_menu_title_delay_status{true}, sub_menu_string_print_status{false},
        sub_menu_content_display_status{false}, sub_menu_display_first_content{true}, sub_menu_add_title_status{false}, sub_menu_add_title_status_extended{false},
        sub_menu_add_content_status{false}, sub_menu_add_content_time_status{false}, sub_menu_edit_content{true};

    char content_main_key{'\0'}, sub_menu_content_cursor_character{'\0'};
    COORD sub_menu_add_content_cord{0}, sub_menu_add_content_cord_2{0}, sub_menu_add_content_cursor{0};
    string sub_menu_string, sub_menu_content_time_date_text;
    size_t sub_menu_time_now{0};

    /* ------------------------- Clock, Date & Mid Panel ------------------------ */

    bool date_and_separator_display_status{true}, time_update{false};
    struct tm time_now;
    int time_now_min{0};

    /* ----------------------------- Welcome Screen ----------------------------- */

    size_t welcome_printing_start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    const int welcome_printing_duration{1200}, welcome_printing_duration_alternative{1200};
    int temp_welcome_printing_duration{0};
    string welcome_text{"Welcome"}, welcome_text_alternative{"Loading Data"}, welcome_text_alternative_uppercase = welcome_text_alternative;

    transform(welcome_text_alternative.begin(), welcome_text_alternative.end(), welcome_text_alternative.begin(), ::toupper);

    /* --------------------------------- Others --------------------------------- */

    int delay_temp{0};
    bool display_status{true};
    COORD console_cursor{0, 0}, temp_main_menu_coordinate{0, 0}, temp_main_cord{0};

    /* -------------------------------------------------------------------------- */
    /*                                   Methods                                  */
    /* -------------------------------------------------------------------------- */

    /* ---------------- Writing to file for experimental purposes --------------- */

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

    /* ---------------------------- Reading from file --------------------------- */

    for (size_t i{0}; i < main_menu.size(); i++)
        (main_menu.at(i)).get_data_from_file();

    /* -------------------------------------------------------------------------- */
    /*                               Welcome Screen                               */
    /* -------------------------------------------------------------------------- */

    system("cls");

    set_console_size(405, 270);
    get_console_size(console_width, console_height);
    set_font_size(21, 44.125, 800);

    /* ------------------------------ Primary Style ----------------------------- */

    // console_cursor.X = (console_width * .50) - welcome_text.length() / 2;
    // console_cursor.Y = (console_height * .45);
    // set_console_cursor(console_cursor);

    // temp_welcome_printing_duration = (welcome_printing_duration - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() + welcome_printing_start) / welcome_text.length();

    // for (size_t i{0}; i < welcome_text.length(); i++)
    // {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(temp_welcome_printing_duration));
    //     console_cursor_status(false);

    //     SetConsoleTextAttribute(color, 11);
    //     cout << "\b\b" << welcome_text.at(i) << " ";

    //     SetConsoleTextAttribute(color, 8);
    //     // cout << char(175);
    //     cout << ">";
    // }
    // cout << " ";
    // std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // for (size_t i{0}; i < welcome_text.length(); i++)
    // {
    //     cout << "\b\b\b\b "
    //          << "<"
    //          << " ";
    //     std::this_thread::sleep_for(std::chrono::milliseconds(temp_welcome_printing_duration * 7 / 10));
    // }

    /* ---------------------------- Alternative Style --------------------------- */

    temp_welcome_printing_duration = (welcome_printing_duration_alternative - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() + welcome_printing_start) / (2 * welcome_text.length());

    console_cursor.X = (console_width * .50) - welcome_text_alternative.length() / 2;
    console_cursor.Y = (console_height * .45);
    set_console_cursor(console_cursor);
    console_cursor_status(false);

    SetConsoleTextAttribute(color, 11);

    cout << welcome_text_alternative << endl;

    for (int j{0}; j < 3; j++)
    {
        set_console_cursor(console_cursor);

        for (size_t i{0}; i < welcome_text_alternative.length(); i++)
        {
            cout << welcome_text_alternative_uppercase.at(i);

            std::this_thread::sleep_for(std::chrono::milliseconds(temp_welcome_printing_duration));

            cout << '\b' << welcome_text_alternative.at(i);
        }
    }

    /* ---------------------- Main Interface Initialization --------------------- */

    set_font_size(9, 19.125, 600);
    console_width = 1100;
    console_height = 650;
    set_console_size(console_width, console_height);
    console_width = 0;
    console_height = 0;
    console_cursor_status(false);

    /*-------------------------------------Odyssey-------------------------------------*/

    while (1)
    {
        // Get main_key

        // main_key = '\0';

        if (temp_key != '\0')
        {
            main_key = temp_key;
            temp_key = '\0';
        }

        if (_kbhit())
            main_key = _getch();

        /* -------------------------------------------------------------------------- */
        /*                        Console Size & Initialization                       */
        /* -------------------------------------------------------------------------- */

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

            /* ------------------------------- Left Panel ------------------------------- */

            // Main Menu
            left_main_x_start = (console_width * 5) / 100;
            left_main_y_start = console_height / 5;
            left_main_height = (console_height * 0.75);

            // Sub Menu
            left_sub_x_start = left_main_x_start + 4;

            /* -------------------------------- Mid Panel ------------------------------- */

            // Clock over Mid Panel
            clock_y_start = (console_height * 5) / 100;
            clock_x_start = (console_width * 38) / 100 - 1;

            // Separator

            mid_x_start = (console_width * 38) / 100 - 2;
            mid_y_start = (console_height * 20) / 100;
            mid_y_end = (console_height * 85) / 100;
            mid_height = mid_y_end - mid_y_start;

            /* ------------------------------- Right Panel ------------------------------ */

            right_x_start = (console_width * 45) / 100;
            right_y_start = console_height / 5;
            right_x_width = ((console_width - right_x_start) * 85 / 100);

            console_width_temp = console_width;
            console_height_temp = console_height;

            system("cls");
            console_cursor_status(false);

            display_status = true;
            console_size_change_status = true;
            sub_menu_string_print_status = true;

            if (sub_menu_add_content_status)
                sub_menu_content_display_status = true;

            if (sub_menu_content_display_status || sub_menu_add_title_status || sub_menu_add_content_status)
                sub_menu_title_display_status = true;

            main_menu_title_display_status = true;

            main_menu_title_delay_status = main_menu_title_line >= 0 ? false : true;
            sub_menu_title_delay_status = sub_menu_title_line >= 0 ? false : true;
            date_and_separator_display_status = true;
        }

        console_cursor_status(false);

        /* -------------------------------------------------------------------------- */
        /*                                    Clock                                   */
        /* -------------------------------------------------------------------------- */

        if (!console_size_change_status)
        {
            // console_size_and_initialization:

            get_local_time(time_now);
            if (time_now.tm_sec != time_now_min)
            {
                time_update = true;
                goto display_clock;

            update_clock_values:

                time_update = false;
                time_now_min = time_now.tm_sec;
            }

            if (sub_menu_add_title_status)
                goto sub_menu_add_title_point;
            else if (sub_menu_add_content_status)
                goto sub_menu_add_content_point;
        }

        /* --------------------------- Down Arrow main_key -------------------------- */

        if (main_key == 0x50)
        {
            if (sub_menu_content_display_status)
            {
                sub_menu_content_line++;

            down_arrow_sub_menu_content_display_point:

                if (sub_menu_content_line >= ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size())
                    sub_menu_content_line = 0;

                int sub_menu_content_max_display_exception = sub_menu_content_max_display;

                if (main_menu_title_line == 2)
                    sub_menu_content_max_display_exception = sub_menu_reminder_content_max_display;

                if (sub_menu_content_line <= sub_menu_content_max_display_exception / 2)
                    sub_menu_content_display_line = 0;
                else if (sub_menu_content_line >= ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() - sub_menu_content_max_display_exception / 2)
                {
                    if (((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() >= sub_menu_content_max_display_exception)
                        sub_menu_content_display_line = ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() - sub_menu_content_max_display_exception;

                    if (((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() < sub_menu_content_max_display_exception)
                        sub_menu_content_display_line = 0;
                }
                else
                    sub_menu_content_display_line = sub_menu_content_line - sub_menu_content_max_display_exception / 2;
            }

            else if (sub_menu_title_display_status)
            {
                sub_menu_title_line++;

            down_arrow_sub_menu_title_display_point:

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

        /* ---------------------------- Up Arrow main_key --------------------------- */

        else if (main_key == 0x48)
        {
            if (sub_menu_content_display_status)
            {
                sub_menu_content_line--;
                if (sub_menu_content_line < 0)
                    sub_menu_content_line = ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() - 1;

                int sub_menu_content_max_display_exception = sub_menu_content_max_display;

                if (main_menu_title_line == 2)
                    sub_menu_content_max_display_exception = sub_menu_reminder_content_max_display;

                if (sub_menu_content_line <= sub_menu_content_max_display_exception / 2)
                    sub_menu_content_display_line = 0;
                else if (sub_menu_content_line >= ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() - sub_menu_content_max_display_exception / 2)
                {
                    if (((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() >= sub_menu_content_max_display_exception)
                        sub_menu_content_display_line = ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() - sub_menu_content_max_display_exception;

                    if (((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() < sub_menu_content_max_display_exception)
                        sub_menu_content_display_line = 0;
                }
                else
                    sub_menu_content_display_line = sub_menu_content_line - sub_menu_content_max_display_exception / 2;
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

        /* -------------------------------- Enter key ------------------------------- */

        if (main_key == 13)
        {
            if (sub_menu_content_display_status && sub_menu_content_line >= 0)
            {
                if (sub_menu_content_line == 0)
                {

                enter_sub_menu_add_content_point:

                    sub_menu_add_content_status = true;
                    sub_menu_string_print_status = true;
                    sub_menu_display_first_content = true;

                    sub_menu_content_being_added = 0;

                    sub_menu_string.clear();
                    sub_menu_time_now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

                    // if (sub_menu_edit_content)
                    //     sub_menu_string = (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content(2);
                }
                else
                    (((main_menu).at(main_menu_title_line)).get_content_reference(sub_menu_title_line))->toggle(sub_menu_content_line); // toggle the status

                display_status = true;
            }

            else if (sub_menu_title_display_status && sub_menu_title_line >= 0)
            {
                if (sub_menu_title_line == 0)
                {
                    switch (main_menu_title_line)
                    {
                    case 0:
                    case 1:
                    case 2:
                        sub_menu_add_title_status = true;
                        sub_menu_string_print_status = true;

                        sub_menu_string.clear();
                        sub_menu_time_now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

                        break;

                    default:
                        break;
                    }
                }
                else
                    sub_menu_content_display_status = true;

                display_status = true;
            }

            else if (main_menu_title_display_status && main_menu_title_line >= 0)
            {
                sub_menu_title_display_status = true;

                system("cls");
                date_and_separator_display_status = true;

                display_status = true;
            }
        }

        /* ------------------------------- Delete key ------------------------------- */

        if (main_key == 'd')
        {
            if (sub_menu_content_display_status && sub_menu_content_line >= 0)
            {
                if (sub_menu_content_line != 0)
                {
                    (((main_menu).at(main_menu_title_line)).get_content_reference(sub_menu_title_line))->delete_content(sub_menu_content_line);
                    if (sub_menu_content_line >= (((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size())
                        sub_menu_content_line = (((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() - 1;

                    main_key = '\0';
                    goto down_arrow_sub_menu_content_display_point;
                }
            }

            else if (sub_menu_title_display_status && sub_menu_title_line >= 0)
            {
                if (sub_menu_title_line != 0)
                {
                    ((main_menu).at(main_menu_title_line)).delete_content(sub_menu_title_line);
                    if (sub_menu_title_line >= ((main_menu).at(main_menu_title_line)).get_content_number())
                        sub_menu_title_line = ((main_menu).at(main_menu_title_line)).get_content_number() - 1;
                }

                main_key = '\0';
                goto down_arrow_sub_menu_title_display_point;
            }
            display_status = true;
        }

        /* ------------------------------- Escape key ------------------------------- */

        if (main_key == 27)
        {
        exit_sub_menu:

            if (sub_menu_content_display_status)
            {
                sub_menu_content_display_status = false;

                sub_menu_title_display_status = true;

                sub_menu_content_line = 0;
            }

            else if (sub_menu_title_display_status)
            {
                sub_menu_title_display_status = false;

                main_menu_title_display_status = true;
                sub_menu_title_delay_status = true;

                sub_menu_title_line = -1;
                sub_menu_title_line_2 = 0;
                sub_menu_title_display_line = 0;

                system("cls");
                date_and_separator_display_status = true;
            }

            else if (main_menu_title_display_status)
            {
                for (size_t i{0}; i < main_menu.size(); i++)
                    main_menu.at(i).add_data_to_file();

                break;
            }
            display_status = true;
        }

        /* -------------------------------------------------------------------------- */
        /*                               Display Status                               */
        /* -------------------------------------------------------------------------- */

        if (display_status)
        {
            display_status = false;
            main_key = '\0';

            /* -------------------------------------------------------------------------- */
            /*                                 Mid Section                                */
            /* -------------------------------------------------------------------------- */

            if (date_and_separator_display_status)
            {

                /* --------------------------- Clock over Mid Pane -------------------------- */

            display_clock:

                string time_str;
                get_time_now(time_str); // getting time now
                SetConsoleTextAttribute(color, 9);
                console_cursor.X = clock_x_start - (time_str.length() / 2);
                console_cursor.Y = clock_y_start;
                set_console_cursor(console_cursor);
                cout << time_str;

                if (time_update)
                    goto update_clock_values;

                get_date_now(time_str); // getting date now
                console_cursor.X = clock_x_start - (time_str.length() / 2);
                console_cursor.Y += 1;
                set_console_cursor(console_cursor);
                cout << time_str;

                /* -------------------------------- Separator ------------------------------- */

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
            date_and_separator_display_status = false;

            /* -------------------------------------------------------------------------- */
            /*                                 Left Panel                                 */
            /* -------------------------------------------------------------------------- */

            /* ------------------------- Main Menu Title Display ------------------------ */

            if (main_menu_title_display_status)
            {
                console_cursor.X = left_main_x_start;
                console_cursor.Y = left_main_y_start;

                (main_menu_title_line_2 != main_menu_title_line) ? delay_temp = main_menu_delay_duration : delay_temp = 0;

                int temp_height{0}, temp_size{0};

                if (sub_menu_title_display_status)
                {
                    temp_size = (sub_menu_title_max_display <= (main_menu.at(main_menu_title_line)).get_content_number())
                                    ? sub_menu_title_max_display * 2 + 1
                                    : (main_menu.at(main_menu_title_line)).get_content_number() * 2 + 1;

                    // temp_height = left_main_height - temp_size;
                }
                // else
                // temp_height = left_main_height;
                temp_height = ceil(left_main_height - temp_size);

                size_t temp_height_space{temp_height / (main_menu.size())};

                for (size_t i{0}; i < main_menu.size(); i++)
                {
                    set_console_cursor(console_cursor);

                    if (i == main_menu_title_line)
                    {
                        temp_main_menu_coordinate = console_cursor;

                        if (sub_menu_title_display_status)
                            console_cursor.Y += temp_size;
                    }

                    temp_main_cord = console_cursor;
                    (main_menu_title_line == i) ? SetConsoleTextAttribute(color, 12) : SetConsoleTextAttribute(color, 11);

                    if (main_menu_title_delay_status)
                    {
                        main_menu.at(i).set_coordinate(console_cursor);

                        char temp_char = delay_print((main_menu.at(i)).get_title(), delay_temp);
                        if (temp_char != '\0')
                        {
                            delay_temp = 0;
                            temp_key = temp_char;
                        }
                    }

                    else
                    {

                        COORD temp_console_cursor{0};
                        get_console_cursor(temp_console_cursor);

                        if ((main_menu.at(main_menu_title_line)).get_content_number() <= sub_menu_title_max_display)
                        {
                            set_console_cursor((main_menu.at(i)).get_coordinate());
                            cout << string(mid_x_start - left_main_x_start - 3, ' ');
                        }

                        set_console_cursor(temp_console_cursor);
                        main_menu.at(i).set_coordinate(get_console_cursor());

                        if (sub_menu_title_display_status || main_menu_title_line != i)
                            cout << (main_menu.at(i)).get_title() << endl;

                        if (!sub_menu_title_display_status && i == main_menu.size() - 1)
                        {
                            // Printing Main Menu Description

                            console_cursor.X = right_x_start + ((console_width - right_x_start) * .50) - (((main_menu).at(main_menu_title_line)).get_description().length() / 2 + 1);
                            console_cursor.Y = right_y_start + left_main_height * .35;

                            set_console_cursor(console_cursor);
                            SetConsoleTextAttribute(color, 15);

                            cout << string(main_menu.at(main_menu_title_line).get_highest_main_description_length() / 2, '\b')
                                 << string(main_menu.at(main_menu_title_line).get_highest_main_description_length() / 2, ' ')
                                 << ((main_menu).at(main_menu_title_line)).get_description()
                                 << string(main_menu.at(main_menu_title_line).get_highest_main_description_length() - ((main_menu).at(main_menu_title_line)).get_description().length() / 2, ' ')
                                 << endl;

                            // Printing Delay Main Menu Title

                            SetConsoleTextAttribute(color, 6);
                            set_console_cursor(temp_main_menu_coordinate);
                            cout << string(mid_x_start - left_sub_x_start - 3, ' ');

                            set_console_cursor(temp_main_menu_coordinate);
                            temp_key = delay_print((main_menu.at(main_menu_title_line)).get_title(), delay_temp);
                        }
                    }

                    console_cursor = temp_main_cord;
                    console_cursor.Y += temp_height_space;
                }
            }

            main_menu_title_line_2 = main_menu_title_line;

            main_menu_title_delay_status = false;

            /*------------------------------------Sub Menu Title Display------------------------------------*/

            if (sub_menu_title_display_status)
            {
                main_menu_title_display_status = false; // Stopping Main Menu printing

                // Removing Previously printed sub menu titles if these are less than sub_menu_max_display

                if ((main_menu.at(main_menu_title_line)).get_content_number() < sub_menu_title_max_display)
                {
                    console_cursor.Y = temp_main_menu_coordinate.Y;
                    for (size_t i{0}; i < ((main_menu.at(main_menu_title_line)).get_content_number() + 1) * 2; i++)
                    {
                        console_cursor.X = left_sub_x_start;
                        console_cursor.Y += 1;
                        set_console_cursor(console_cursor);
                        cout << string(mid_x_start - left_sub_x_start - 3, ' ');
                    }
                }

                console_cursor = temp_main_menu_coordinate;
                console_cursor.X = left_sub_x_start;

                (sub_menu_title_line_2 != sub_menu_title_line && !sub_menu_add_title_status_extended) ? delay_temp = sub_menu_delay_duration : delay_temp = 0;

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
                                 << string(mid_x_start - left_sub_x_start - (((main_menu.at(main_menu_title_line)).get_content(temp_sub_menu_title_line)).get_title()).length() - 3, ' ')
                                 << endl;
                        }

                        if (!sub_menu_content_display_status && i == temp_size - 1)
                        {
                            // Printing Sub Menu Content

                            if (main_menu_title_line == 1)
                            {
                                console_cursor.X = right_x_start;
                                console_cursor.Y = right_y_start;
                                for (size_t j{0}; j <= mid_height; j++)
                                {
                                    console_cursor.Y = right_y_start + j;
                                    set_console_cursor(console_cursor);
                                    cout << string(console_width - right_x_start, ' ') << endl;
                                }

                                if (sub_menu_title_line == 0)
                                {
                                    console_cursor.X = right_x_start;
                                    console_cursor.Y = right_y_start;
                                    set_console_cursor(console_cursor);
                                    SetConsoleTextAttribute(color, 10);
                                    cout << char(175) << " " << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(0);
                                }
                                else
                                {
                                    console_cursor.X = right_x_start;
                                    console_cursor.Y = right_y_start;
                                    set_console_cursor(console_cursor);
                                    cout << string(console_width - right_x_start, ' ');

                                    int underline_width = ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(1).length() >
                                                                  ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_time(1).length() + ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_date(1).length() + 2
                                                              ? ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(1).length()
                                                              : ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_time(1).length() + ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_date(1).length() + 2;

                                    console_cursor.X = console_width - 10 - ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(1).length();
                                    console_cursor.Y = right_y_start;

                                    set_console_cursor(console_cursor);
                                    SetConsoleTextAttribute(color, 14);
                                    cout << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(1);

                                    console_cursor.X = right_x_start;
                                    console_cursor.Y++;
                                    set_console_cursor(console_cursor);
                                    cout << string(console_width - right_x_start, ' ');

                                    console_cursor.X = console_width - 10 - underline_width;
                                    // console_cursor.Y++;
                                    set_console_cursor(console_cursor);
                                    SetConsoleTextAttribute(color, 6);
                                    for (size_t i{0}; i < underline_width; i++)
                                        cout << char(196);

                                    console_cursor.X = right_x_start;
                                    console_cursor.Y++;
                                    set_console_cursor(console_cursor);
                                    cout << string(console_width - right_x_start, ' ');

                                    console_cursor.X = console_width - 10 - (((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_time(1).length() + ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_date(1).length() + 2);
                                    // console_cursor.Y++;
                                    set_console_cursor(console_cursor);
                                    SetConsoleTextAttribute(color, 8);
                                    cout << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_time(1)
                                         << ", "
                                         << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_date(1);

                                    SetConsoleTextAttribute(color, 15);

                                    if (((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() >= 3)
                                    {
                                        int sub_menu_string_display_x{0};
                                        string temp_content_string = ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(2);

                                        console_cursor.X = right_x_start;
                                        console_cursor.Y = right_y_start + 4;
                                        set_console_cursor(console_cursor);
                                        for (size_t i{0}; i < temp_content_string.length(); i++)
                                        {
                                            cout << temp_content_string.at(i);
                                            sub_menu_string_display_x++;
                                            if (i > 1 && sub_menu_string_display_x % right_x_width == 0 || temp_content_string.at(i) == '\n')
                                            {
                                                if (((temp_content_string.at(i) >= 'a' && temp_content_string.at(i) <= 'z') || (temp_content_string.at(i) >= 'A' && temp_content_string.at(i) <= 'Z')) && ((temp_content_string.at(i + 1) >= 'a' && temp_content_string.at(i + 1) <= 'z') || (temp_content_string.at(i + 1) >= 'A' && temp_content_string.at(i + 1) <= 'Z')))
                                                    cout << '-';
                                                sub_menu_string_display_x = 0;
                                                console_cursor.X = right_x_start;
                                                console_cursor.Y++;
                                                set_console_cursor(console_cursor);
                                            }
                                        }
                                    }
                                }
                            }

                            else if (!sub_menu_add_title_status_extended)
                            {
                                console_cursor.X = right_x_start;
                                for (size_t j{0}; j <= sub_menu_content_max_display * 2 + 1; j++)
                                {
                                    console_cursor.Y = right_y_start + j;
                                    set_console_cursor(console_cursor);
                                    cout << string(console_width - right_x_start, ' ') << endl;
                                }

                                int sub_menu_content_max_display_exception{sub_menu_content_max_display};
                                if (main_menu_title_line == 2)
                                    sub_menu_content_max_display_exception = sub_menu_reminder_content_max_display;

                                int temp_sub_menu_content_max_display = ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() <= sub_menu_content_max_display_exception
                                                                            ? ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size()
                                                                            : sub_menu_content_max_display_exception + 1;

                                (((main_menu).at(main_menu_title_line)).get_content_reference(sub_menu_title_line))->sort();

                                for (size_t j{0}; j < temp_sub_menu_content_max_display; j++)
                                {
                                    if (j != 0 || sub_menu_title_line == 0 || temp_sub_menu_content_max_display <= 1)
                                    {
                                        console_cursor.X = right_x_start;

                                        if (sub_menu_title_line == 0 || temp_sub_menu_content_max_display <= 1)
                                            console_cursor.Y = right_y_start;
                                        else if (main_menu_title_line == 2)
                                            console_cursor.Y = right_y_start + (3 * (j - 1));
                                        else
                                            console_cursor.Y = right_y_start + (2 * (j - 1));

                                        set_console_cursor(console_cursor);

                                        int color_code = 15;
                                        if (main_menu_title_line == 2)
                                            color_code = 3;
                                        if (j == 0)
                                            color_code = 10;
                                        if ((((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_active_status(j) == char(251))
                                            color_code = 8;

                                        if (sub_menu_title_line != 0 && temp_sub_menu_content_max_display <= 1)
                                        {
                                            SetConsoleTextAttribute(color, 8);
                                            cout << char(175) << " Nothing added";
                                        }
                                        else
                                        {
                                            ((((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_active_status(j) == char(251))
                                                ? SetConsoleTextAttribute(color, 10)
                                                : SetConsoleTextAttribute(color, color_code);

                                            cout << (((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_active_status(j)
                                                 << ' ';
                                            SetConsoleTextAttribute(color, color_code);
                                            cout << (((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(j);
                                        }

                                        if (main_menu_title_line == 2 && sub_menu_title_line != 0 && temp_sub_menu_content_max_display > 1)
                                        {
                                            console_cursor.X += 2;
                                            console_cursor.Y += 1;
                                            set_console_cursor(console_cursor);
                                            ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_active_status(j) == char(251)
                                                ? SetConsoleTextAttribute(color, 8)
                                                : SetConsoleTextAttribute(color, 15);

                                            cout << (((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_time(j)
                                                 << ", "
                                                 << (((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_date(j);
                                        }
                                    }
                                }
                            }

                            // Delay Printing Sub Menu Title

                            SetConsoleTextAttribute(color, 6);
                            set_console_cursor(temp_cord);
                            cout << string(mid_x_start - left_sub_x_start - 3, ' ');
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

                if (sub_menu_add_title_status_extended)
                {
                    sub_menu_add_title_status_extended = false;
                    sub_menu_content_display_status = true;
                    sub_menu_edit_content = false;
                    // sub_menu_add_content_status = true;
                    goto enter_sub_menu_add_content_point;
                }

                if ((main_menu.at(main_menu_title_line)).get_content_number() == 0)
                    goto exit_sub_menu;
            }

            /*------------------------------------Sub Menu Content Display--------------------------------------*/

            if (sub_menu_content_display_status)
            {
            sub_menu_content_display_point:

                main_menu_title_display_status == false; // Stopping Main Menu printing
                sub_menu_title_display_status == false;  // Stopping Sub Menu title printing

                if (main_menu_title_line == 1)
                {

                    console_cursor.X = right_x_start;
                    console_cursor.Y = right_y_start;
                    set_console_cursor(console_cursor);
                    cout << string(console_width - right_x_start, ' ');

                    int underline_width = ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(1).length() >
                                                  ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_time(1).length() + ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_date(1).length() + 2
                                              ? ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(1).length()
                                              : ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_time(1).length() + ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_date(1).length() + 2;

                    console_cursor.X = console_width - 10 - ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(1).length();
                    console_cursor.Y = right_y_start;

                    set_console_cursor(console_cursor);
                    SetConsoleTextAttribute(color, 14);
                    cout << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(1);

                    console_cursor.X = console_width - 10 - underline_width;
                    console_cursor.Y++;
                    set_console_cursor(console_cursor);
                    SetConsoleTextAttribute(color, 6);
                    for (size_t i{0}; i < underline_width; i++)
                        cout << char(196);

                    console_cursor.X = console_width - 10 - (((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_time(1).length() + ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_date(1).length() + 2);
                    console_cursor.Y++;
                    set_console_cursor(console_cursor);
                    SetConsoleTextAttribute(color, 8);
                    cout << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_time(1)
                         << ", "
                         << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_date(1);

                    if (sub_menu_edit_content)
                    {
                        sub_menu_add_content_status = true;
                        sub_menu_string_print_status = true;
                        sub_menu_display_first_content = true;

                        sub_menu_content_being_added = 0;

                        sub_menu_string = (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content(1);
                        sub_menu_time_now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    }
                }

                // if (main_menu_title_line == 1)
                // {
                //     console_cursor.X = right_x_start;
                //     console_cursor.Y = right_y_start;
                //     set_console_cursor(console_cursor);
                //     cout << string(console_width - right_x_start, ' ');

                //     int underline_width = ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(1).length() >
                //                                   ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_time(1).length() + ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_date(1).length() + 2
                //                               ? ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(1).length()
                //                               : ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_time(1).length() + ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_date(1).length() + 2;

                //     console_cursor.X = console_width - 10 - ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(1).length();
                //     console_cursor.Y = right_y_start;

                //     set_console_cursor(console_cursor);
                //     SetConsoleTextAttribute(color, 14);
                //     cout << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(1);

                //     console_cursor.X = console_width - 10 - underline_width;
                //     console_cursor.Y++;
                //     set_console_cursor(console_cursor);
                //     SetConsoleTextAttribute(color, 6);
                //     for (size_t i{0}; i < underline_width; i++)
                //         cout << char(196);

                //     console_cursor.X = console_width - 10 - (((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_time(1).length() + ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_date(1).length() + 2);
                //     console_cursor.Y++;
                //     set_console_cursor(console_cursor);
                //     SetConsoleTextAttribute(color, 8);
                //     cout << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_time(1)
                //          << ", "
                //          << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_date(1);

                //     if (((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() >= 3)
                //     {
                //         int sub_menu_string_display_x{0};
                //         string temp_content_string = ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(2);

                //         console_cursor.X = right_x_start;
                //         console_cursor.Y = right_y_start + 4;
                //         set_console_cursor(console_cursor);
                //         for (size_t i{0}; i < temp_content_string.length(); i++)
                //         {
                //             cout << temp_content_string.at(i);
                //             sub_menu_string_display_x++;
                //             if (i > 1 && sub_menu_string_display_x % right_x_width == 0 || temp_content_string.at(i) == '\n')
                //             {
                //                 if (((temp_content_string.at(i) >= 'a' && temp_content_string.at(i) <= 'z') || (temp_content_string.at(i) >= 'A' && temp_content_string.at(i) <= 'Z')) && ((temp_content_string.at(i + 1) >= 'a' && temp_content_string.at(i + 1) <= 'z') || (temp_content_string.at(i + 1) >= 'A' && temp_content_string.at(i + 1) <= 'Z')))
                //                     cout << '-';
                //                 sub_menu_string_display_x = 0;
                //                 console_cursor.X = right_x_start;
                //                 console_cursor.Y++;
                //                 set_console_cursor(console_cursor);
                //             }
                //         }
                //     }
                // }

                if (main_menu_title_line == 0 || main_menu_title_line == 2)
                {

                    int sub_menu_content_max_display_exception{sub_menu_content_max_display};
                    if (main_menu_title_line == 2)
                        sub_menu_content_max_display_exception = sub_menu_reminder_content_max_display;

                    int temp_sub_menu_content_max_display =
                        ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size() < sub_menu_content_max_display_exception
                            ? ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size()
                            : sub_menu_content_max_display_exception;

                    int temp_sub_menu_content_display_line = sub_menu_content_display_line;

                    if (main_menu_title_line != 1)
                        ((main_menu.at(main_menu_title_line)).get_content_reference(sub_menu_title_line))->sort();

                    for (size_t i{0}; i < temp_sub_menu_content_max_display; i++)
                    {
                        console_cursor.X = right_x_start;
                        if (main_menu_title_line == 2 && temp_sub_menu_content_display_line > 0)
                            console_cursor.Y = right_y_start + (3 * i);
                        else
                            console_cursor.Y = right_y_start + (2 * i);

                        set_console_cursor(console_cursor);

                        int color_code = 15;
                        if (main_menu_title_line == 2)
                            color_code = 3;
                        if (temp_sub_menu_content_display_line == 0)
                            color_code = 10;
                        if (((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_active_status(temp_sub_menu_content_display_line) == char(251))
                            color_code = 8;
                        if (temp_sub_menu_content_display_line == sub_menu_content_line)
                            color_code = 6;

                        if (main_menu_title_line == 2 && sub_menu_content_being_added == 1 && sub_menu_add_content_status && temp_sub_menu_content_display_line == 0)
                        {
                            temp_sub_menu_content_max_display--;
                            SetConsoleTextAttribute(color, 3);
                            cout
                                << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_active_status(0)
                                << " "
                                << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content((main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content_size() - 1)
                                << string(console_width - right_x_start - ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content((main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content_size() - 1).length() - 2, ' ') << endl;
                        }
                        else
                        {
                            ((((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_active_status(temp_sub_menu_content_display_line) == char(251))
                                ? SetConsoleTextAttribute(color, 10)
                                : SetConsoleTextAttribute(color, color_code);

                            cout << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_active_status(temp_sub_menu_content_display_line)
                                 << " ";

                            SetConsoleTextAttribute(color, color_code);
                            cout << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(temp_sub_menu_content_display_line)
                                 << string(console_width - right_x_start - ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content(temp_sub_menu_content_display_line).length() - 2, ' ') << endl;
                        }

                        console_cursor.Y += 1;
                        set_console_cursor(console_cursor);
                        cout << string(console_width - right_x_start - (((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_time(temp_sub_menu_content_display_line).length() - (((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_date(temp_sub_menu_content_display_line).length() - 3, ' ') << endl;

                        if (main_menu_title_line == 2 && sub_menu_title_line != 0 && temp_sub_menu_content_display_line != 0)
                        {
                            console_cursor.X += 2;
                            set_console_cursor(console_cursor);
                            ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_active_status(temp_sub_menu_content_display_line) == char(251)
                                ? SetConsoleTextAttribute(color, 8)
                                : SetConsoleTextAttribute(color, 15);

                            cout << (((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_time(temp_sub_menu_content_display_line)
                                 << ", "
                                 << (((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_date(temp_sub_menu_content_display_line)
                                 << string(console_width - right_x_start - (((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_time(temp_sub_menu_content_display_line).length() - (((main_menu).at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_date(temp_sub_menu_content_display_line).length() - 3, ' ') << endl;
                        }

                        if (++temp_sub_menu_content_display_line >= ((main_menu.at(main_menu_title_line)).get_content(sub_menu_title_line)).get_content_size())
                            temp_sub_menu_content_display_line = 0;
                    }

                    console_cursor.X = right_x_start;
                    for (size_t i{0}; i < 3; i++)
                    {
                        console_cursor.Y++;
                        set_console_cursor(console_cursor);
                        cout << string(console_width - right_x_start, ' ') << endl;
                    }
                }
                if (main_menu_title_line == 1 && sub_menu_content_being_added == 1 && sub_menu_add_content_status)
                    goto sub_menu_add_content_diary_enter_key_point;
                if (main_menu_title_line == 2 && sub_menu_content_being_added == 1 && sub_menu_add_content_status && sub_menu_add_content_time_status)
                    goto sub_menu_add_content_reminder_enter_key_point;
            }

            /* -------------------------------------------------------------------------- */
            /*                             Add Sub Menu Title                             */
            /* -------------------------------------------------------------------------- */

            if (sub_menu_add_title_status)
            {
                main_menu_title_display_status = false;  // Stopping Main Menu printing
                sub_menu_title_display_status = false;   // Stopping Sub Menu title printing
                sub_menu_content_display_status = false; // Stopping Sub Menu content printing

                while (1)
                {
                    goto console_size_and_initialization;

                sub_menu_add_title_point:

                    SetConsoleTextAttribute(color, 15);

                    console_cursor.X = left_sub_x_start + 3 + sub_menu_string.length();
                    console_cursor.Y = temp_main_menu_coordinate.Y + 2;
                    set_console_cursor(console_cursor);

                    if ((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - sub_menu_time_now) % 1000 >= 500)
                        // cout << char(222);
                        cout << "|";
                    else
                        cout << " ";

                    if (sub_menu_string_print_status)
                    {
                        SetConsoleTextAttribute(color, 15);

                        console_cursor.X = left_sub_x_start;
                        console_cursor.Y = temp_main_menu_coordinate.Y + 2;
                        set_console_cursor(console_cursor);
                        cout << string(mid_x_start - left_sub_x_start - 3, ' ');

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
                        else if (content_main_key == 13 && sub_menu_string.length() > 0)
                        {

                            console_cursor.X = left_sub_x_start;
                            console_cursor.Y = temp_main_menu_coordinate.Y + 2;
                            set_console_cursor(console_cursor);
                            cout << string(mid_x_start - left_sub_x_start - 3, ' ');

                            main_menu.at(main_menu_title_line).add_content(Side_Menu());
                            sub_menu_title_line = (main_menu.at(main_menu_title_line)).get_content_number() - 1;
                            (main_menu.at(main_menu_title_line).get_content_reference(sub_menu_title_line))->set_title(sub_menu_string);

                            if ((main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content_size() < sub_menu_title_max_display)
                                main_menu_title_display_status = true;

                            if (main_menu_title_line == 1)
                            {
                                (main_menu.at(main_menu_title_line).get_content_reference(sub_menu_title_line))->set_content(1, sub_menu_string);

                                if (!sub_menu_edit_content)
                                {
                                    (main_menu.at(main_menu_title_line).get_content_reference(sub_menu_title_line))->add_content_time((main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content_time_composite(0));
                                    (main_menu.at(main_menu_title_line).get_content_reference(sub_menu_title_line))->add_content_date((main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content_date_composite(0));
                                }
                            }

                            sub_menu_add_title_status_extended = true;

                            break;
                        }

                        else if (content_main_key == 27)
                        {
                            sub_menu_title_line = 0;
                            sub_menu_add_title_status_extended = false;

                            break;
                        }
                    }
                }

                sub_menu_string.clear();

                sub_menu_add_title_status = false;
                sub_menu_title_display_status = true;

                goto down_arrow_sub_menu_title_display_point;
            }

            /* -------------------------------------------------------------------------- */
            /*                            Add Sub Menu Content                            */
            /* -------------------------------------------------------------------------- */

            if (sub_menu_add_content_status)
            {
                main_menu_title_display_status = false;  // Stopping Main Menu printing
                sub_menu_title_display_status = false;   // Stopping Sub Menu title printing
                sub_menu_content_display_status = false; // Stopping Sub Menu content printing

                temp_sub_menu_content_max_display = (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content_size() < sub_menu_content_max_display
                                                        ? (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content_size()
                                                        : sub_menu_content_max_display;

                while (1)
                {
                    goto console_size_and_initialization;

                sub_menu_add_content_point:

                    SetConsoleTextAttribute(color, 15);

                    sub_menu_content_cursor_character = '|';
                    console_cursor.X = right_x_start + sub_menu_string.length() + 2;
                    console_cursor.Y = right_y_start + sub_menu_content_being_added;

                    if (main_menu_title_line == 1)
                    {
                        if (sub_menu_content_being_added == 0)
                        {
                            console_cursor.X = console_width - 10;
                            console_cursor.Y = right_y_start;
                        }
                        if (sub_menu_content_being_added == 1)
                        {
                            // set_console_cursor(sub_menu_add_content_cursor);
                            console_cursor = sub_menu_add_content_cursor;
                            // if ((sub_menu_string.length() % right_x_width) == 0)
                            // console_cursor.X = right_x_start + sub_menu_add_content_diary_newline_last_number;
                            // ((sub_menu_string.length() % right_x_width) == 0
                            //                                         ? 1
                            //                                         : (sub_menu_string.length() % right_x_width));

                            // if (sub_menu_add_content_diary_newline_printed)
                            // {
                            //     console_cursor.X = right_x_start + 1;
                            //     sub_menu_add_content_diary_newline_printed = false;
                            // }
                            // console_cursor.Y = right_y_start + sub_menu_add_content_diary_newline_threshold + sub_menu_add_content_diary_newline_number;
                        }
                    }

                    else if (sub_menu_content_being_added == 1 && main_menu_title_line == 2)
                    {
                        if (sub_menu_add_content_time_status)
                            sub_menu_content_time_date_text = "HH:MM";
                        else
                            sub_menu_content_time_date_text = "DD-MM-YYYY";

                        sub_menu_content_cursor_character = sub_menu_content_time_date_text.at(sub_menu_string.length());

                        if (!sub_menu_add_content_time_status)
                            console_cursor.X += (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content_time((main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content_size() - 1).length() + 2;

                        if (sub_menu_string.length() >= 4)
                        {
                            console_cursor.X += 2;
                            sub_menu_content_cursor_character = sub_menu_content_time_date_text.at(sub_menu_string.length() + 2);
                        }
                        else if (sub_menu_string.length() >= 2)
                        {
                            console_cursor.X++;
                            sub_menu_content_cursor_character = sub_menu_content_time_date_text.at(sub_menu_string.length() + 1);
                        }

                        SetConsoleTextAttribute(color, 8);
                    }

                    set_console_cursor(console_cursor);

                    /* ------------------ Printing content until key is pressed ----------------- */

                    if (sub_menu_display_first_content)
                    {
                        SetConsoleTextAttribute(color, 8);
                        if (main_menu_title_line == 1)
                        {
                            // cout << "\b\b  ";
                            console_cursor.X = console_width - 10 - (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content(1).length();
                            console_cursor.Y = right_y_start;
                            set_console_cursor(console_cursor);
                            cout << (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content(1) << endl;

                            console_cursor.X = console_width - 10;
                            console_cursor.Y = right_y_start;
                            set_console_cursor(console_cursor);
                            // cout << '\b';
                        }
                        else if (main_menu_title_line == 0 || main_menu_title_line == 2)
                        {
                            cout << "\b\b" << char(175);
                            set_console_cursor(console_cursor);
                            cout << (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content(temp_sub_menu_content_display_line) << endl;
                            set_console_cursor(console_cursor);
                            cout << '\b';
                        }
                        SetConsoleTextAttribute(color, 15);
                    }

                    if ((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - sub_menu_time_now) % 1000 >= 500)
                        cout << sub_menu_content_cursor_character;
                    else
                        cout << " ";

                    // Printing Sub Menu String

                    if (sub_menu_string_print_status)
                    {
                        if (main_menu_title_line == 1)
                        {
                            if (sub_menu_content_being_added == 0)
                            {
                                console_cursor.X = right_x_start;
                                console_cursor.Y = right_y_start + sub_menu_content_being_added;
                                set_console_cursor(console_cursor);
                                cout << string(console_width - right_x_start, ' ') << endl;
                                set_console_cursor(console_cursor);

                                // console_cursor.X = console_width - 11 - (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content(1).length();
                                console_cursor.X = console_width - 10 - sub_menu_string.length();
                                console_cursor.Y = right_y_start;
                                set_console_cursor(console_cursor);
                                cout << sub_menu_string;
                            }
                            else if (sub_menu_content_being_added == 1)
                            {
                                cout << "\b ";
                                console_cursor.X = right_x_start;
                                console_cursor.Y = right_y_start + 4;
                                set_console_cursor(console_cursor);

                                int sub_menu_string_display_x{0};

                                for (size_t i{0}; i < sub_menu_string.length(); i++)
                                {
                                    cout << sub_menu_string.at(i);
                                    sub_menu_string_display_x++;
                                    if (i > 0 && sub_menu_string_display_x % right_x_width == 0 || sub_menu_string.at(i) == '\n')
                                    {
                                        // cout << "\b ";
                                        if (((sub_menu_string.at(i) >= 'a' && sub_menu_string.at(i) <= 'z') || (sub_menu_string.at(i) >= 'A' && sub_menu_string.at(i) <= 'Z')) && ((sub_menu_string.at(i + 1) >= 'a' && sub_menu_string.at(i + 1) <= 'z') || (sub_menu_string.at(i + 1) >= 'A' && sub_menu_string.at(i + 1) <= 'Z')))
                                            cout << '-';

                                        sub_menu_string_display_x = 0;
                                        console_cursor.X = right_x_start;
                                        console_cursor.Y++;
                                        set_console_cursor(console_cursor);
                                    }
                                    cout << "  \b\b";
                                    get_console_cursor(sub_menu_add_content_cursor);
                                }
                            }
                        }
                        else if (main_menu_title_line == 0 || main_menu_title_line == 2)
                        {
                            console_cursor.X = right_x_start;
                            console_cursor.Y = right_y_start + sub_menu_content_being_added;
                            set_console_cursor(console_cursor);
                            cout << string(console_width - right_x_start, ' ') << endl;
                            set_console_cursor(console_cursor);

                            if (sub_menu_content_being_added == 0)
                                cout << (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_active_status(0) << " " << sub_menu_string;

                            else if (sub_menu_content_being_added == 1)
                            {
                                console_cursor.X = right_x_start + 2;
                                set_console_cursor(console_cursor);
                                if (sub_menu_add_content_time_status)
                                {
                                    sub_menu_content_cursor_character = ':';

                                    SetConsoleTextAttribute(color, 8);
                                    cout << "HH" << sub_menu_content_cursor_character << "MM";
                                }
                                else
                                {
                                    SetConsoleTextAttribute(color, 15);
                                    cout << (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content_time((main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content_size() - 1) << ", ";

                                    sub_menu_content_cursor_character = '-';
                                    SetConsoleTextAttribute(color, 8);
                                    cout << "DD" << sub_menu_content_cursor_character << "MM" << sub_menu_content_cursor_character << "YYYY";
                                    console_cursor.X = right_x_start + 2 + (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content_time((main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content_size() - 1).length() + 2;
                                }

                                set_console_cursor(console_cursor);
                                SetConsoleTextAttribute(color, 15);
                                for (size_t i{0}; i < sub_menu_string.length(); i++)
                                {
                                    cout << sub_menu_string.at(i);
                                    if (i == 1 || i == 3)
                                        cout << sub_menu_content_cursor_character;
                                }
                            }
                        }

                        sub_menu_string_print_status = false;
                    }

                    content_main_key = '\0';

                    /* -------------------------------------------------------------------------- */
                    /*                                 Key Actions                                */
                    /* -------------------------------------------------------------------------- */

                    if (_kbhit())
                    {
                        content_main_key = _getch();
                        if (content_main_key >= 32 && content_main_key <= 126)
                        {
                            if (sub_menu_content_being_added == 0)
                                sub_menu_string += content_main_key;

                            else if (main_menu_title_line == 1 && sub_menu_content_being_added == 1)
                                sub_menu_string += content_main_key;

                            else if (main_menu_title_line == 2 && sub_menu_content_being_added == 1)
                            {
                                if (content_main_key >= '0' && content_main_key <= '9')
                                    sub_menu_string += content_main_key;

                                if (sub_menu_add_content_time_status && sub_menu_string.length() >= 4)
                                {
                                sub_menu_add_content_reminder_string_adding_point:
                                    (main_menu.at(main_menu_title_line).get_content_reference(sub_menu_title_line))->add_content_time(sub_menu_string);
                                    sub_menu_add_content_time_status = false;
                                    sub_menu_string.clear();
                                }
                                if (!sub_menu_add_content_time_status && sub_menu_string.length() >= 8)
                                {
                                    (main_menu.at(main_menu_title_line).get_content_reference(sub_menu_title_line))->add_content_date_reverse(sub_menu_string);
                                    sub_menu_string.clear();
                                    sub_menu_content_line = (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content_size() - (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_completed_content_size() - 1;
                                    break;
                                }
                            }

                            sub_menu_string_print_status = true;
                            sub_menu_display_first_content = false;
                        }

                        /* ------------------------------ Backspace Key ----------------------------- */

                        else if (content_main_key == 8 && sub_menu_string.length() > 0)
                        {
                            sub_menu_string.erase(sub_menu_string.begin() + sub_menu_string.length() - 1);
                            // cout << "\b\b  \b\b";
                            cout << "\b\b  ";
                            sub_menu_string_print_status = true;
                        }

                        /* -------------------------------- Enter Key ------------------------------- */

                        else if (content_main_key == 13 && sub_menu_string.length() > 0)
                        {
                            if (main_menu_title_line == 0)
                            {
                                cout << "\b ";
                                (main_menu.at(main_menu_title_line).get_content_reference(sub_menu_title_line))->add_content(sub_menu_string);

                                sub_menu_content_line = (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content_size() - (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_completed_content_size() - 1;
                                break;
                            }
                            else if (main_menu_title_line == 1)
                            {
                                if (sub_menu_content_being_added == 0)
                                {
                                    (main_menu.at(main_menu_title_line).get_content_reference(sub_menu_title_line))->set_content(1, sub_menu_string);
                                    sub_menu_content_line = 0;
                                    // sub_menu_add_content_time_status = true;
                                    sub_menu_content_being_added = 1;

                                    sub_menu_add_content_cursor.X = right_x_start;
                                    sub_menu_add_content_cursor.Y = right_y_start + 4;

                                    if (sub_menu_edit_content)
                                    {
                                        sub_menu_edit_content = false;
                                        sub_menu_string = (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content(2);
                                    }
                                    else
                                        sub_menu_string.clear();

                                    goto sub_menu_content_display_point;

                                sub_menu_add_content_diary_enter_key_point:

                                    sub_menu_string_print_status = true;
                                }
                                else if (sub_menu_content_being_added == 1)
                                {
                                    cout << "\b ";
                                    sub_menu_string += '\n';
                                    sub_menu_add_content_cursor.X = right_x_start;
                                    sub_menu_add_content_cursor.Y++;

                                    // cout << endl
                                    //      << endl
                                    //      //      //  << (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content(2);
                                    //      << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_content_line)).get_content_size();
                                    // for (size_t i{0}; i < ((main_menu.at(main_menu_title_line)).get_content(sub_menu_content_line)).get_content_size(); i++)
                                    //     cout << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_content_line)).get_content(i) << endl;
                                    // Sleep(2000);

                                    // sub_menu_string.clear();

                                    // break;
                                }
                            }

                            // if (sub_menu_content_being_added == 0)
                            // {}
                            // else
                            // {
                            //     sub_menu_content_line = (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content_size() - (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_completed_content_size() - 1;
                            //     // (main_menu.at(main_menu_title_line).get_content_reference(sub_menu_title_line))->add_content_time();
                            // }
                            else if (main_menu_title_line == 2 && sub_menu_content_being_added == 0)
                            {

                                if (sub_menu_content_being_added == 0)
                                {
                                    (main_menu.at(main_menu_title_line).get_content_reference(sub_menu_title_line))->add_content(sub_menu_string);
                                    sub_menu_content_line = 0;
                                    sub_menu_add_content_time_status = true;
                                    sub_menu_content_being_added = 1;

                                    goto sub_menu_content_display_point;

                                sub_menu_add_content_reminder_enter_key_point:

                                    sub_menu_string.clear();
                                    sub_menu_string_print_status = true;
                                }
                                // sub_menu_string_print_status = true;
                            }
                        }

                        /* ------------------------------- Escape Key ------------------------------- */

                        else if (content_main_key == 27)
                        {
                            if (main_menu_title_line == 1)
                            {
                                if (sub_menu_content_being_added == 0)
                                {
                                    cout << "\b ";
                                    sub_menu_content_line = 0;
                                    sub_menu_content_being_added = 1;
                                    sub_menu_display_first_content = false;
                                    sub_menu_add_content_cursor.X = right_x_start;
                                    sub_menu_add_content_cursor.Y = right_y_start + 4;

                                    if (sub_menu_edit_content)
                                    {
                                        sub_menu_edit_content = false;
                                        sub_menu_string = (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content(2);
                                    }

                                    goto sub_menu_content_display_point;
                                }
                                else if (sub_menu_content_being_added == 1)
                                {
                                    if (sub_menu_string.length() > 0)
                                        (main_menu.at(main_menu_title_line).get_content_reference(sub_menu_title_line))->set_content(2, sub_menu_string);
                                    else
                                        (main_menu.at(main_menu_title_line).get_content_reference(sub_menu_title_line))->set_content(2, "Nothing added here");

                                    cout << "\b ";
                                    // sub_menu_content_line = (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content_size();
                                    sub_menu_string.clear();

                                    break;
                                }
                            }
                            if (main_menu_title_line == 2 && sub_menu_add_content_time_status && sub_menu_content_being_added == 1)
                                goto sub_menu_add_content_reminder_string_adding_point;
                            else
                            {
                                sub_menu_content_line = 0;

                                break;
                            }
                        }
                    }
                }

                // cout << endl
                //      << endl
                //      //  << (main_menu.at(main_menu_title_line).get_content(sub_menu_title_line)).get_content(2);
                //      << ((main_menu.at(main_menu_title_line)).get_content(sub_menu_content_line)).get_content_size();
                // Sleep(2000);
                sub_menu_content_being_added = 0;
                sub_menu_add_content_status = false;
                sub_menu_edit_content = true;
                if (main_menu_title_line == 1)
                {
                    sub_menu_title_display_status = true;
                    goto down_arrow_sub_menu_title_display_point;
                }
                else
                {
                    sub_menu_content_display_status = true;
                    goto down_arrow_sub_menu_content_display_point;
                }
            }
        }
    }

    return 0;
}
