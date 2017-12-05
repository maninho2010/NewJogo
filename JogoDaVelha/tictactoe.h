#ifndef TICTACTOE_H_INCLUDED
#define TICTACTOE_H_INCLUDED

#include <stdio.h>
#include "gamefiles.h"

#define IA_NAME  "IA"
#define MAX_NICK 16

//------------------------------------------------------------------------------

typedef struct{
    char nick[MAX_NICK];
    double score;
    char simbolo; //--- X ou O
    int vitorias;
    int empates;
    int qt_jogadas_totais;
}tPlayer;

//------------------------------------------------------------------------------

char **gerar_tabuleiro(size_t dim);

//------------------------------------------------------------------------------

void freeBoard(char **tabuleiro, size_t dim);

//------------------------------------------------------------------------------

void inic_players(tPlayer player[2]);

//------------------------------------------------------------------------------

int da_pra_ganhar(char simbolo, char **tabuleiro, size_t dim, size_t *lin, size_t *col);

//------------------------------------------------------------------------------

void IA_Joga(tPlayer player[2], char **tabuleiro, size_t dim);

//------------------------------------------------------------------------------

void Player_Joga(tPlayer player, char **tabuleiro, int dim);

//------------------------------------------------------------------------------

void inic_ptrTecladoNum(char** tabuleiro, int dim, char *ptr_casa[10]);

//------------------------------------------------------------------------------

int verificar_vitoria(char **tabuleiro, int sz, char c);

//------------------------------------------------------------------------------

void mostrar(char **tabuleiro, int dim);

//-----------------------------------------------------------------------------

void ordenar_ranking(tRanking *ranking, size_t sz);

//------------------------------------------------------------------------------

void Jogar_vs_IA(); // --- Possibilidade de salvar score

//------------------------------------------------------------------------------

void Jogar_vs_Player(); // --- PvP em uma melhor de x

//------------------------------------------------------------------------------

#endif // TICTACTOE_H_INCLUDED
