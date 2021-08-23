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
    setFontSize(10,22,800);
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

    int console_width{0}, console_height{0};
    console_size(&console_width, &console_height);
    vector<Main_Menu> main_menu{0};

    //Left Panel

    //Mid Panel
    int mid_x_mid{0}, mid_y_start{0}, mid_y_end{0}, mid_y;
    mid_x_mid = (console_width * 38) / 100 - 2;
    mid_y_start = (console_height * 18) / 100;
    mid_y_end = (console_height * 85) / 100;
    mid_y = mid_y_end - mid_y_start;

    //Clock over Mid Panel
    int clock_y_start{0}, clock_x_start{0};
    clock_y_start = (console_height * 5) / 100;
    clock_x_start = (console_width * 38) / 100 - 7;

    COORD console_cursor{0, 0};

    //temporary code---------------------------------- experimental purpose
    {

        Side_Menu t1, t2, t3, t4;
        t1.add_object("take breakfast", 0);
        t1.add_content("taken");

        t2.add_object("take lunch", 0);
        t2.add_content("nope");

        t3.add_object("take breakfast", 0);
        t3.add_content("taken");

        t4.add_object("take lunch", 0);
        t4.add_content("nope");

        Main_Menu temp, temp2, temp3;
        temp.add_object("To Do List", 0);
        temp.add_content(t1);
        main_menu.push_back(temp);
        (main_menu.at(0)).add_content(t2);
        (main_menu.at(0)).add_content(t3);
        (main_menu.at(0)).add_content(t4);

        temp2.add_object("Diary", 0);
        temp2.add_content(t2);
        main_menu.push_back(temp2);

        temp3.add_object("Reminders", 0);
        main_menu.push_back(temp3);
    }

    console_cursor.X = 0;
    console_cursor.Y = 0;
    COORD menu_cordinate{0, 0};
    console_cursor_status(false);

    char key;
    int line{-1};
    int sub_line{-1};
    bool display_chk{true}, sub_menu_delay_print{true};
    bool main_menu_status{false};
    bool sub_menu_status{false};
    bool main_menu_access{false};

    while (1)
    {
        key = '\0';
        if (_kbhit())
            key = _getch();

        if (key == 0x50)
        {
            if (sub_menu_status == true)
            {
                sub_line++;
                if (sub_line < ((main_menu.at(line)).get_content_number()))
                    main_menu_status = true;
                else
                    sub_line--;
            }
            else
            {
                line++;
                if (line < main_menu.size())
                    display_chk = true;
                else
                    line--;
            }
        }
        else if (key == 0x48)
        {
            if (sub_menu_status == true)
            {
                if (sub_line > 0)
                {
                    sub_line--;
                    main_menu_status = true;
                }
                else
                    sub_line--;
            }
            else if (line > 0)
            {
                line--;
                display_chk = true;
            }
        }
        if (key == 13)
        {
            if(sub_menu_status==true){
                (((main_menu).at(line)).get_content_address(sub_line))->toggle();//toggle the status
               main_menu_status = true;//this introduces unexpected behaviours
            }
            else if (main_menu_access == true)
            {
                main_menu_status = true;
                sub_menu_status = true;
                main_menu_access = false;
            }
            
        }

        if (key == 27)
        {
        exit_sub_menu:
            if (sub_menu_status == true)
            {
                main_menu_status = false;
                sub_menu_status = false;
                display_chk = true;
                sub_line = -1;
                sub_menu_delay_print = true;
            }
            else
                break;
        }

        // system("cls");

        //Left Side
        if (display_chk == true || main_menu_status == true)
        {
            // std::this_thread::sleep_for(std::chrono::seconds(1));

            system("cls");

            //Clock over Mid Panel
            string time_str;
            get_time_now(time_str); //geting time now
            SetConsoleTextAttribute(color, 9);
            console_cursor.X = clock_x_start+2;
            console_cursor.Y = clock_y_start;
            set_console_cursor(console_cursor);
            cout<<time_str;
            
            get_date_now(time_str); //getting date now
            console_cursor.X = clock_x_start;
            console_cursor.Y +=1;
            set_console_cursor(console_cursor);
            cout<<time_str;


            SetConsoleTextAttribute(color, 15);
            for (size_t i{0}; i < mid_y; i++)
            {
                console_cursor.X = mid_x_mid;
                console_cursor.Y = mid_y_start + i;
                set_console_cursor(console_cursor);
                char border_char=char(221);
                SetConsoleTextAttribute(color, 8);
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

            console_cursor.X = 0;
            console_cursor.Y = 0;

            for (size_t i{0}; i < main_menu.size(); i++)
            {
                console_cursor.X = (console_width * 5) / 100;

                if (line == i)
                {
                    SetConsoleTextAttribute(color, 6);
                    console_cursor.Y += 5;
                    set_console_cursor(console_cursor);
                    if (main_menu_status == true)
                    {
                        ((main_menu).at(i)).set_cordinator(console_cursor);
                        console_cursor.Y += (main_menu.at(i)).get_content_number() * 2;
                    }
                    cout << (main_menu.at(i)).get_title() << endl;
                    main_menu_access = true;
                }
                else
                {
                    SetConsoleTextAttribute(color, 11);
                    console_cursor.Y += 5;
                    set_console_cursor(console_cursor);
                    cout << (main_menu.at(i)).get_title() << endl;
                }
            }

            if (main_menu_status == true)
            {
                console_cursor = ((main_menu).at(line)).get_cordinator();
                console_cursor.X = (console_width * 5) / 100 + 4;

                for (size_t i{0}; i < (main_menu.at(line)).get_content_number(); i++)
                {
                    (sub_line == i) ? SetConsoleTextAttribute(color, 6) : SetConsoleTextAttribute(color, 15);

                    console_cursor.Y += 2;
                    set_console_cursor(console_cursor);
                    COORD cord = console_cursor;

                    if (sub_menu_delay_print == true)
                        delay_print(((main_menu.at(line)).get_content(i)).get_title(), 200);

                    else
                        cout << ((main_menu.at(line)).get_content(i)).get_title() << endl;

                    if (sub_line == i)
                    {
                        console_cursor.X = (console_width * 45) / 100;
                        console_cursor.Y = 5;
                        set_console_cursor(console_cursor);

                        for (size_t j{0}; j < (((main_menu).at(line)).get_content(i)).get_content_size(); j++)
                            cout<< (((main_menu).at(line)).get_content(i)).get_active_status() 
                            <<' '<< (((main_menu).at(line)).get_content(i)).get_content(j) << endl;
                    }
                    console_cursor = cord;
                }
                sub_menu_delay_print = false;
                main_menu_status = false;
                sub_menu_status = true;
                if ((main_menu.at(line)).get_content_number() == 0)
                    goto exit_sub_menu;
            }

            display_chk = false;
        }
    }
    return 0;
}