//
//  Additions.cpp
//  Radio Station
//
//  Created by Eduardo Almeida on 13/05/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include "Additions.h"

#ifdef WIN32 // Windows includes
#include <windows.h>
#include <conio.h>
#else // Non-Windows  (POSIX) includes
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#ifndef WIN32
int getch() {
    struct termios oldt,
    newt;
    int            ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}
#endif

namespace Additions {
    void waitForReturn() {
        while(1) { // Wait 'till Keyboard hit ...
            int ch = getch();
            
            if (ch == 13 || ch == 10)
                break;
        }
    }
    
    std::vector<std::string> explode(const std::string &delimiter, const std::string &str) {
        std::vector<std::string> arr;
        
        int strleng = (int) str.length();
        int delleng = (int) delimiter.length();
        
        if (delleng == 0)
            return arr;
        
        int i = 0;
        int k = 0;
        
        while (i < strleng) {
            int j = 0;
            while (i + j < strleng && j < delleng && str[i + j] == delimiter[j])
                j++;
            
            if (j == delleng) {
                arr.push_back(str.substr(k, i-k));
                i += delleng;
                k = i;
            } else {
                i++;
            }
        }
        
        arr.push_back(  str.substr(k, i-k) );
        return arr;
    }
    
    std::string get_file_contents(const char *filename) {
        std::ifstream in (filename, std::ios::in | std::ios::binary);
        if (in) {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            return(contents);
        }
        throw(errno);
    }
    
    //
    // Asks for a string, but allows the user to simply press
    // return in order to accept the default value.
    //
    
    std::string ask_for_str_or_return() {
        char ch = getch();
        
        if ((int)ch == 13 || (int)ch == 10)
            return "";
        
        std::string str;
        
        while ((int)ch != 13 && (int)ch != 10) {
            if ((int)ch == 127) {
                if (str.size() > 0) {
                    str = str.erase(str.size() - 1);
                    
                    std::cout << '\b';
                    std::cout << " ";
                    std::cout << '\b';
                }
            } else {
                std::string strToAppend(&ch);
                
                str += strToAppend;
            }
            
            std::cout << &ch;
            
            ch = getch();
        }
        
        return str;
    }
    
    bool checkForOnlyNumeric(std::string str) {
        std::string::const_iterator it = str.begin();
        while (it != str.end() && std::isdigit(*it)) ++it;
        return !str.empty() && it == str.end();
    }
    
    void clearConsole() {
#ifndef WIN32
        write(1,"\E[H\E[2J",7);
#else
        COORD upperLeftCorner = {0,0};
        DWORD charsWritten;
        DWORD conSize;
        HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO  csbi;
        
        GetConsoleScreenBufferInfo(hCon, &csbi);
        conSize = csbi.dwSize.X * csbi.dwSize.Y;
        
        FillConsoleOutputCharacter(hCon, TEXT(' '), conSize, upperLeftCorner, &charsWritten);
        GetConsoleScreenBufferInfo(hCon, &csbi);
        FillConsoleOutputAttribute(hCon, csbi.wAttributes, conSize, upperLeftCorner, &charsWritten);
        
        SetConsoleCursorPosition(hCon, upperLeftCorner);
#endif
    }
}
