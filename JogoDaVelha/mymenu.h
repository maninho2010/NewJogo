#ifndef MYMENU_H_INCLUDED
#define MYMENU_H_INCLUDED

#include "stdio.h"

//------------------------------------------------------------------------------

int Criar_Menu(char **menu, size_t menu_sz, char *title);

//------------------------------------------------------------------------------

int Criar_Menu_Basico(char **menu, int sz, char *title);

//------------------------------------------------------------------------------

void home();

//------------------------------------------------------------------------------

void escolher_oponente();

//------------------------------------------------------------------------------

#endif // MYMENU_H_INCLUDED