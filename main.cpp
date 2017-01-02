#include <iostream>
#include <windows.h>
#include <conio.h>
void cheat(char game_num){
    DWORD x_memo_addr = 0;
    DWORD y_memo_addr = 0;
    std::string g_name = "";
    if(game_num == '2'){     //Alice Mare
        std::cout << "You choosen => Alice Mare!" << std::endl;
        x_memo_addr = 0x078978C;
        y_memo_addr = 0x0789790;
        g_name = "Alice mare      F4: Change Display / F8: Info";
    }else if(game_num == '1'){
        std::cout << "You choosen => Ib game!" << std::endl;
        g_name = "Ib";
    }else{
        std::cout << "Unknown game number, please choose another!" << std::endl;
    }
    HWND hWnd = FindWindow(0, g_name.c_str());
    if(!hWnd){
        std::cout << "Couldn't find the game process" << std::endl;
    } else {
        DWORD process_ID;
        GetWindowThreadProcessId(hWnd,&process_ID);
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_ID);
        if(!hProcess){
            std::cout << "Couldn't open the process" << std::cout;
        }else {
            //The code below just make the game character to walk around and draw a rectangle.
            bool forever = true;
            int x_axis = 0;
            int y_axis = 0;
            ReadProcessMemory(hProcess,(void*)x_memo_addr,&x_axis,sizeof(x_axis),0);
            ReadProcessMemory(hProcess,(void*)y_memo_addr,&y_axis,sizeof(y_axis),0);
            DWORD xsize = sizeof(x_axis);
            DWORD ysize = sizeof(y_axis);
            int x1 = x_axis;
            int y1 = y_axis;
            int x2 = x_axis;
            int y2 = y_axis;
            int maxi = x_axis + 5;
            int mayi = y_axis + 5;
            while(forever){
                while(x1 < maxi){
                    x1 += 1;
                    WriteProcessMemory(hProcess, (LPVOID)x_memo_addr, &x1, xsize, NULL);
                    Sleep(1000);
                }

                while(y1 < mayi){
                    y1 += 1;
                    WriteProcessMemory(hProcess, (LPVOID)y_memo_addr, &y1, ysize, NULL);
                    Sleep(1000);
                }

                while(x1 > maxi - 5){
                    x1 -= 1;
                    WriteProcessMemory(hProcess, (LPVOID)x_memo_addr, &x1, xsize, NULL);
                    Sleep(1000);
                }

                while(y1 > mayi - 5){
                    y1 -= 1;
                    WriteProcessMemory(hProcess, (LPVOID)y_memo_addr, &y1, ysize, NULL);
                    Sleep(1000);
                }
            }


        }
    }

}
int main(){
    SetConsoleTitle("RPGMaker All-In-One Hack");
    char c_game = 0;
    std::cout << "Please choose a game below! (Press the specified number on keyboard)" << std::endl;
    std::cout << "1. Ib\n2. Alice Mare" << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;
    std::cin >> c_game;
    cheat(c_game);
}
