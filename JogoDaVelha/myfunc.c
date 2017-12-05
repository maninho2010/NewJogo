#include <stdio.h>
#include <conio.h>
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#include <unistd.h>
#endif
 #if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif
#include "myfunc.h"

//------------------------------------------------------------------------------

void dormir(int ms)
{
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    usleep(ms * 1000);
    #endif // defined
    #if defined(_WIN32) || defined(_WIN64)
    Sleep(ms);
    #endif // defined
}

//------------------------------------------------------------------------------

void pause()
{

    printf("\nPRESSIONE <ENTER> PARA CONTINUAR...");
    while(getch() != 13) continue;
    fflush(stdin);
}

//------------------------------------------------------------------------------

void limpar_tela()
{
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
    #endif // defined
    #if defined(_WIN32) || defined(_WIN64)
    system("cls");
    #endif // defined
}

//------------------------------------------------------------------------------
