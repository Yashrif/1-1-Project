#include <bits/stdc++.h>
#include <chrono>
#include <windows.h>
#include <string>
#include "Main_Menu.h"
#include "Side_Menu.h"

HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);

void get_console_cursor(COORD &cordinator)
{
    CONSOLE_SCREEN_BUFFER_INFO console_cursor;
    GetConsoleScreenBufferInfo(out_handle, &console_cursor);
    cordinator.X = console_cursor.dwCursorPosition.X;
    cordinator.Y = console_cursor.dwCursorPosition.Y;
}

void set_console_cursor(const COORD &cordinator)
{
    SetConsoleCursorPosition(out_handle, cordinator);
}

void console_cursor_status(bool status)
{
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(out_handle, &cursor_info);
    cursor_info.bVisible = status;
    SetConsoleCursorInfo(out_handle, &cursor_info);
}

void get_console_size(int &x, int &y)
{
    CONSOLE_SCREEN_BUFFER_INFO cursor_buffer;
    GetConsoleScreenBufferInfo(out_handle, &cursor_buffer);
    // x = cursor_buffer.dwSize.X ;
    x = cursor_buffer.srWindow.Right - cursor_buffer.srWindow.Left + 1;
    y = cursor_buffer.srWindow.Bottom - cursor_buffer.srWindow.Top + 1;
}

void set_console_size(int x, int y)
{
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);

    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, x, y, TRUE);
}

char delay_print(std::string title, int time_milliseconds)
{
    char key{'\0'};
    size_t time_now{0}, time_now_2{0};
    int i{0};
    time_milliseconds = time_milliseconds / title.length();
    while (1)
    {
        time_now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        if (time_now - time_now_2 >= time_milliseconds)
        {
            std::cout << title[i];
            i++;
            if (i == title.length())
                break;
            time_now_2 = time_now;
        }
        if (_kbhit())
        {
            key = _getch();
            time_milliseconds = 0;
        }
    }
    return key;
}

void get_local_time(struct tm &ltm)
{
    time_t now = time(0);
    localtime_s(&ltm, &now);
}
void get_date_now(std::string &returnval)
{
    struct tm ltm;
    get_local_time(ltm);

    std::string months[] = {"nanimo", "January", "February",
                            "March", "April", "May", "June", "July", "August",
                            "September", "October", "November", "December"};
    returnval = "";
    std::string tm;
    tm += std::to_string(ltm.tm_mday);
    if (tm.size() < 2)
        tm = "0" + tm;

    returnval += tm + " " + months[ltm.tm_mon + 1] + ", ";
    returnval += std::to_string(1900 + ltm.tm_year);
}

void get_time_now(std::string &returnval)
{
    struct tm ltm;
    get_local_time(ltm);

    int hour_now = ltm.tm_hour;
    std::string pm_am = " AM";
    if (hour_now >= 12)
    {
        pm_am = " PM", hour_now -= 12;
        if (!hour_now)
            hour_now = 12;
    }
    else if (!hour_now)
        hour_now = 12;

    returnval = std::to_string(hour_now) + ':';
    (ltm.tm_min < 10) ? returnval += "0" + std::to_string(ltm.tm_min) : returnval += std::to_string(ltm.tm_min);
    returnval += pm_am;
}

void set_font_size(int width, int height, int weight)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = width;  // Width of each character in the font
    cfi.dwFontSize.Y = height; // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = weight;                //normal weight is 400, while 700 is bold,use multiple of 100
    std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void customized_input(string &string_value)
{
    string_value = '\0';
    COORD temp_cord;
    get_console_cursor(temp_cord);

    char key{'\0'};
    while (1)
    {
        key = '\0';

        if (_kbhit())
        {
            key = _getch();
            if (key >= 32 && key <= 126)
            {
                string_value += key;
                set_console_cursor(temp_cord);
                cout << string_value;
            }
            else if (key == 13 || key == 27)
            {
                break;
            }
        }
    }

}
void customized_input(string &string_value, int mid_x, int left_x)
{
    string_value = '\0';
    COORD temp_cord;
    get_console_cursor(temp_cord);
    bool space_print{true};

    char key{'\0'};
    while (1)
    {
        key = '\0';

        if (_kbhit())
        {
            key = _getch();
            if (key >= 32 && key <= 126)
            {
                if (space_print)
                {
                    cout << string(mid_x - left_x, ' ');
                    space_print = false;
                }
                string_value += key;
                set_console_cursor(temp_cord);
                cout << string_value;
            }
            else if (key == 13 || key == 27)
            {
                break;
            }
        }
    }

}

void customized_input(vector<string> &string_value, int end_point, int starting_point)
{
    string_value.clear();
    string_value.push_back(string());

    int size{0};
    COORD temp_cord;
    get_console_cursor(temp_cord);
    bool space_print{true}, enter_status{false};

    char key{'\0'};
    while (1)
    {

        if (space_print)
        {
            set_console_cursor(temp_cord);
            cout << string(end_point - starting_point, ' ');
            set_console_cursor(temp_cord);
            cout << char(254) << " ";
            space_print = false;
        }

        key = '\0';

        if (_kbhit())
        {
            key = _getch();
            if (key >= 32 && key <= 126)
            {
                string_value.at(size) += key;
                set_console_cursor(temp_cord);
                cout << char(254) << " " << string_value.at(size);
                enter_status = true;
            }
            else if (key == 13 && enter_status)
            {
                string_value.push_back(string());
                size++;
                space_print = true;
                temp_cord.Y += 2;

                enter_status = false;
            }

            else if (key == 27)
            {
                break;
            }
        }
    }

}
