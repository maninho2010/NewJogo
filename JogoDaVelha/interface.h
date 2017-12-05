#ifndef VELHAFACE_H_INCLUDED
#define VELHAFACE_H_INCLUDED

#include "tictactoe.h"
#include "gamefiles.h"

//------------------------------------------------------------------------------

void ranking();

//------------------------------------------------------------------------------

void creditos();

//------------------------------------------------------------------------------

void Tutorial(int dim);

//------------------------------------------------------------------------------

int caraOuCoroa(char *nome1, char *nome2);

//------------------------------------------------------------------------------

void escolher_nicks(char nick1[MAX_NICK], char nick2[MAX_NICK], int bool_IA);

//------------------------------------------------------------------------------

int jogar_mais();

//------------------------------------------------------------------------------

int perguntar(char *sentence);

//------------------------------------------------------------------------------

void IA_Game_Interface(tPlayer player[2], char **tabuleiro, size_t dim);    //-- Incluso scores

//------------------------------------------------------------------------------

void PvP_Game_Interface(tPlayer player[2], unsigned short serie, char **tabuleiro, size_t dim); //--- Melhor de x

//------------------------------------------------------------------------------

void Interface_ganhador(tPlayer player, char **tabuleiro, size_t dim);

//------------------------------------------------------------------------------

void Interface_empate(tPlayer player[2], char **tabuleiro, size_t dim);

//------------------------------------------------------------------------------

void mostrar_status(tPlayer player[2]);

//------------------------------------------------------------------------------

void mostrar_ranking(tRanking *ranking, int n_elem);

//------------------------------------------------------------------------------

#endif // VELHAFACE_H_INCLUDED
