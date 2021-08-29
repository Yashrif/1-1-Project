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
    set_font_size(9, 19.125, 600);
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

    int console_width{0}, console_height{0};
    vector<Main_Menu> main_menu{0};

    /*-----------Titles-------*/

    //Left Panel
    int left_main_x{0}, left_main_y{0}, left_sub_x{0}, left_sub_y{0}, left_y;

    //Mid Panel
    int mid_x_mid{0}, mid_y_start{0}, mid_y_end{0}, mid_y;

    //Clock over Mid Panel
    int clock_y_start{0}, clock_x_start{0};

    /*--------Transition---------*/

    const int main_menu_delay{150}, sub_menu_delay{100}, max_sub_menu_display{5};

    COORD console_cursor{0, 0};

    //temporary code---------------------------------- experimental purpose
    {

        Side_Menu t1, t2, t3, t4, t5, t6, t7, t8;
        t1.set_title("take breakfast");
        t1.add_content("taken");

        t2.set_title("take lunch");
        t2.add_content("nope");

        t3.set_title("take breakfast");
        t3.add_content("taken");

        t4.set_title("take lunch");
        t4.add_content("nope");

        t5.set_title("take lunch");
        t5.add_content("nope");

        t6.set_title("take lunch");
        t6.add_content("nope");

        t7.set_title("take lunch");
        t7.add_content("nope");

        t8.set_title("take lunch");
        t8.add_content("nope");

        Main_Menu temp, temp2, temp3;
        temp.set_title("To Do List");
        main_menu.push_back(temp);
        (main_menu.at(0)).add_content(t1);
        (main_menu.at(0)).add_content(t2);
        (main_menu.at(0)).add_content(t3);
        (main_menu.at(0)).add_content(t4);
        (main_menu.at(0)).add_content(t5);
        (main_menu.at(0)).add_content(t6);
        (main_menu.at(0)).add_content(t7);
        (main_menu.at(0)).add_content(t8);

        temp2.set_title("Diary");
        main_menu.push_back(temp2);
        (main_menu.at(1)).add_content(t1);
        (main_menu.at(1)).add_content(t2);
        (main_menu.at(1)).add_content(t3);
        (main_menu.at(1)).add_content(t4);
        (main_menu.at(1)).add_content(t4);
        temp2.add_content(t2);

        temp3.set_title("Reminders");
        main_menu.push_back(temp3);
        (main_menu.at(2)).add_content(t2);
        (main_menu.at(2)).add_content(t3);
        (main_menu.at(2)).add_content(t4);
        (main_menu.at(2)).add_content(t4);
    }

    console_cursor.X = 0;
    console_cursor.Y = 0;
    COORD menu_cordinate{0, 0};
    console_cursor_status(false);

    char key;
    int main_line{-1}, sub_line{-1}, sub_display_line{0};
    bool display_chk{true}, main_menu_delay_print{true}, sub_menu_delay_print{true}, sub_max_check{false};
    bool main_menu_status{true}, sub_menu_status{false};
    int console_width_temp, console_height_temp;
    COORD temp_cord{0};

    while (1)
    {
        //Get Key

        key = '\0';
        if (_kbhit())
            key = _getch();

        //Console Size

        console_size(&console_width, &console_height);
        if (console_width != console_width_temp || console_height != console_height_temp)
        {
            //Left Panel
            left_y = (console_height * 80) / 100;
            left_main_x = (console_width * 5) / 100;
            left_main_y = console_height / 5;

            // Mid Panel
            mid_x_mid = (console_width * 38) / 100 - 2;
            mid_y_start = (console_height * 20) / 100;
            mid_y_end = (console_height * 85) / 100;
            mid_y = mid_y_end - mid_y_start;

            //Clock over Mid Panel
            clock_y_start = (console_height * 5) / 100;
            clock_x_start = (console_width * 38) / 100 - 1;
            console_width_temp = console_width;
            console_height_temp = console_height;

            display_chk = true;
            console_cursor_status(false);
        }

        //Down Arrow Key

        if (key == 0x50)
        {
            if (sub_menu_status == true)
            {
                sub_line++;
                if (sub_line >= ((main_menu.at(main_line)).get_content_number()))
                    sub_line = 0;
                if (sub_max_check == true)
                {
                    if (++sub_display_line >= (main_menu.at(main_line)).get_content_number())
                        sub_display_line = 0;
                }

                else if (sub_line < floor(max_sub_menu_display / 2.0))
                    sub_display_line = 0;

                if (sub_line == floor(max_sub_menu_display / 2.0))
                    sub_max_check = true;

                main_menu_status = true;
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
                if (sub_line == (main_menu.at(main_line)).get_content_number() - ceil(max_sub_menu_display / 2.0))
                    sub_max_check = true;

                if (sub_max_check == true)
                {
                    sub_display_line = sub_line - 2;
                    if (sub_display_line < 0)
                        sub_display_line = (main_menu.at(main_line)).get_content_number() + sub_line - 2;
                }
                else if (sub_line > floor(max_sub_menu_display / 2.0))
                {
                    sub_display_line = (main_menu.at(main_line)).get_content_number() - 5;
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
            }
            display_chk = true;
        }

        //Enter Key

        if (key == 13)
        {
            if (sub_menu_status == true)
            {
                (((main_menu).at(main_line)).get_content_address(sub_line))->toggle(); //toggle the status
                display_chk = true;
                main_menu_status = true;
            }
            else if (main_menu_status == true)
            {
                display_chk = true;
                sub_menu_status = true;
            }
        }

        //Escape Key

        if (key == 27)
        {
        exit_sub_menu:
            if (sub_menu_status == true)
            {
                display_chk = true;
                main_menu_status = true;
                sub_menu_status = false;
                sub_menu_delay_print = true;
                sub_max_check = false;

                sub_line = -1;
                sub_display_line = 0;
            }
            else if (main_menu_status == true)
                break;
        }

        if (display_chk == true)
        {
            system("cls");

            //Clock over Mid Panel

            string time_str;
            get_time_now(time_str); //geting time now
            SetConsoleTextAttribute(color, 9);
            console_cursor.X = clock_x_start - (time_str.length() / 2);
            console_cursor.Y = clock_y_start;
            set_console_cursor(console_cursor);
            cout << time_str;

            get_date_now(time_str); //getting date now
            console_cursor.X = clock_x_start - (time_str.length() / 2);
            console_cursor.Y += 1;
            set_console_cursor(console_cursor);
            cout << time_str;

            //Mid Panel

            SetConsoleTextAttribute(color, 15);
            for (size_t i{0}; i < mid_y; i++)
            {
                console_cursor.X = mid_x_mid;
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

            /*--------------Left Panel----------*/

            //Main Panel

            if (main_menu_status == true)
            {
                console_cursor.X = left_main_x;
                console_cursor.Y = left_main_y;

                int temp{0};
                (sub_menu_status == true) ? temp = left_y - max_sub_menu_display * 2 : temp = left_y;

                for (size_t i{0}; i < main_menu.size(); i++)
                {

                    if (sub_menu_status == true)
                    {
                        if (i <= main_line)
                        {
                            console_cursor.Y = left_main_y + ceil((temp * i) / 4.0);
                            ((main_menu).at(i)).set_cordinator(console_cursor);
                        }
                        else
                            console_cursor.Y = left_main_y + ceil((temp * i) / 4.0) + (max_sub_menu_display * 2);
                    }
                    else
                        console_cursor.Y = left_main_y + ceil((temp * i) / 4.0);

                    (main_line == i) ? SetConsoleTextAttribute(color, 12) : SetConsoleTextAttribute(color, 11);
                    set_console_cursor(console_cursor);

                    if (main_menu_delay_print == true)
                        delay_print((main_menu.at(i)).get_title(), main_menu_delay);

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
                            delay_print((main_menu.at(main_line)).get_title(), main_menu_delay);
                        }
                    }
                }
            }
            main_menu_delay_print = false;

            //Sub Panel

            if (sub_menu_status == true)
            {
                console_cursor = ((main_menu).at(main_line)).get_cordinator();
                console_cursor.X = (console_width * 5) / 100 + 4;

                int temp{0};
                (max_sub_menu_display <= (main_menu.at(main_line)).get_content_number()) ? temp = max_sub_menu_display : temp = (main_menu.at(main_line)).get_content_number();
                int temp_sub_line = sub_display_line;
                for (size_t i{0}; i < temp; i++)
                {
                    console_cursor.Y += 2;
                    set_console_cursor(console_cursor);
                    COORD cord{console_cursor};
                    SetConsoleTextAttribute(color, 15);

                    if (sub_menu_delay_print == true)
                        delay_print(((main_menu.at(main_line)).get_content(temp_sub_line)).get_title_serial(), ((main_menu.at(main_line)).get_content(temp_sub_line)).get_title(), sub_menu_delay);

                    else
                    {
                        if (sub_line == temp_sub_line)
                            temp_cord = console_cursor;
                        else
                            (cout << ((main_menu.at(main_line)).get_content(temp_sub_line)).get_title_serial() << ". " << ((main_menu.at(main_line)).get_content(temp_sub_line)).get_title() << endl);
                        if (i == temp - 1)
                        {
                            SetConsoleTextAttribute(color, 6);
                            set_console_cursor(temp_cord);
                            delay_print(((main_menu.at(main_line)).get_content(sub_line)).get_title_serial(), ((main_menu.at(main_line)).get_content(sub_line)).get_title(), sub_menu_delay);
                        }
                    }

                    if (sub_line == temp_sub_line)
                    {
                        console_cursor.X = (console_width * 45) / 100;
                        console_cursor.Y = 5;
                        set_console_cursor(console_cursor);
                        SetConsoleTextAttribute(color, 15);

                        for (size_t j{0}; j < (((main_menu).at(main_line)).get_content(temp_sub_line)).get_content_size(); j++)
                            cout << (((main_menu).at(main_line)).get_content(temp_sub_line)).get_active_status()
                                 << ' ' << (((main_menu).at(main_line)).get_content(temp_sub_line)).get_content(j) << endl;
                    }
                    console_cursor = cord;
                    if (++temp_sub_line >= (main_menu.at(main_line)).get_content_number())
                        temp_sub_line = 0;
                }
                sub_menu_delay_print = false;
                if ((main_menu.at(main_line)).get_content_number() == 0)
                    goto exit_sub_menu;
            }
            display_chk = false;
        }
    }
    return 0;
}