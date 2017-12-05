#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gamefiles.h"
#include "interface.h"
#include "tictactoe.h"
#include "myfunc.h"

//------------------------------------------------------------------------------

char **gerar_tabuleiro(size_t dim)
{
    int i,j;
    char **tabuleiro = (char **)malloc(dim * sizeof(char*));

    for(i = 0; i < dim; i++)
    {
        tabuleiro[i] = (char*)malloc(dim * sizeof(char));
        for(j = 0; j < dim; j++)
        {
            tabuleiro[i][j] = ' ';
        }
    }

    return tabuleiro;
}

//------------------------------------------------------------------------------

void freeBoard(char **tabuleiro, size_t dim)
{
    int i;

    for(i = 0; i < dim; i++)
    {
        free(tabuleiro[i]);
    }
    free(tabuleiro);
}

//------------------------------------------------------------------------------

void inic_players(tPlayer player[2])
{
    strcpy(player[0].nick, "Player 1");
    player[0].simbolo = 'X';
    player[0].score = 0.0;
    player[0].vitorias = 0;
    player[0].empates = 0;
    player[0].qt_jogadas_totais = 0;

    strcpy(player[0].nick, "Player 2");
    player[1].simbolo = 'O';
    player[1].score = 0.0;
    player[1].vitorias = 0;
    player[1].empates = 0;
    player[1].qt_jogadas_totais = 0;
}

//------------------------------------------------------------------------------

int da_pra_ganhar(char simbolo, char **tabuleiro, size_t dim, size_t *lin, size_t *col)
{
    int i, j;
    int sequencia, qt_espaco;

    // --- VERIFICA AS LINHAS
    for(i = 0; i < dim; i++)
    {
        sequencia = qt_espaco = 0;
        for(j = 0; j < dim; j++)
        {
            if(tabuleiro[i][j] == simbolo)
            {
                ++sequencia;
            }
            else if(tabuleiro[i][j] == ' ') //--- Salva a posicao vazia, caso der pra ganhar
            {
                ++qt_espaco;
                *lin = i;
                *col = j;
            }
        }

        if(sequencia == 2 && qt_espaco == 1)
        {
            return 1;
        }
    }

    // --- VERIFICA AS COLUNAS
    for(j = 0; j < dim; j++)
    {
        sequencia = qt_espaco = 0;
        for(i = 0; i < dim; i++)
        {
            if(tabuleiro[i][j] == simbolo)
            {
                ++sequencia;
            }
            else if(tabuleiro[i][j] == ' ')
            {
                ++qt_espaco;
                *lin = i;
                *col = j;
            }
        }

            if(sequencia == 2 && qt_espaco == 1)
                return 1;
    }

    // --- CHECA A DIAGONAL PRINCIPAL [ TOPO ESQUERDO - BASE DIREITA ]
    sequencia = qt_espaco = 0;
    for(i = 0; i < dim; i++)
    {
        if(tabuleiro[i][i]  == simbolo)
        {
            ++sequencia;
        }
        else if(tabuleiro[i][i] == ' ')
        {
            ++qt_espaco;
            *lin = *col = i;
        }
    }
    if(sequencia == 2 && qt_espaco == 1)
        return 1;

    // --- CHECA A DIAGONAL [ BASE ESQUERDA - TOPO DIREITO ]
    sequencia = qt_espaco = 0;
    j = 0;
    for(i = dim-1; i >= 0; --i)
    {
        if(tabuleiro[i][j] == simbolo)
        {
            ++sequencia;
        }
        else if(tabuleiro[i][j] == ' ')
        {
            ++qt_espaco;
            *lin = i;
            *col = j;
        }
        ++j;
    }
        if(sequencia == 2 && qt_espaco == 1)
            return 1;

    return 0;
}

//------------------------------------------------------------------------------

void IA_Joga(tPlayer player[2], char **tabuleiro, size_t dim)
{

    // --- VERIFICA SE DA PRA GANHAR
    // --- VERIFICA SE DA PRA PERDER
    // --- ESCOLHE UMA POSICAO VALIDA ALEATORIA

    size_t lin;
    size_t col;

    if(da_pra_ganhar(player[1].simbolo, tabuleiro, dim, &lin, &col))
    {
        tabuleiro[lin][col] = player[1].simbolo;
    }
    else if(da_pra_ganhar(player[0].simbolo, tabuleiro, dim, &lin, &col))
    {
        tabuleiro[lin][col] = player[1].simbolo;
    }
    else
    {
        while(1)
        {
            lin = rand() % dim;
            col = rand() % dim;
                if(tabuleiro[lin][col] == ' ')
                {
                    tabuleiro[lin][col] = player[1].simbolo;
                    break;
                }
        }
    }
}

//------------------------------------------------------------------------------

void Player_Joga(tPlayer player, char **tabuleiro, int dim)
{
    char c_pos = 0;
    int pos = 0;
    char* ptr_pos[10]; /* APONTA PARA AS CASAS DO TABULEIRO
        POSICOES SEMELHANTES AO TECLADO NUMERICO
        POSICAO '0' EH IGNORADA
           |   |
         7 | 8 | 9
        ---|---|---
         4 | 5 | 6
        ---|---|---
         1 | 2 | 3
           |   |
    */
    //--- Para dim  maior que 3
    char c_linha = 0, c_coluna = 0;
    size_t linha = 0, coluna = 0;
    // ---

    printf("\nSua vez %s '%c'", player.nick, player.simbolo);

    if(dim == 3)
    {
        inic_ptrTecladoNum(tabuleiro, dim, ptr_pos); /* FAZ OS PONTEIROS APONTAR PARA AS CASAS DO TABULEIRO */

        while(1)
        {
            printf("\n\nPosicao: ");
            scanf(" %c", &c_pos);
            fflush(stdin);

            pos = c_pos - '0';

            if(pos >= 1 && pos <= 9 && *ptr_pos[pos] == ' ') /* POSICAO VALIDA */
            {
                *ptr_pos[pos] = player.simbolo; /* COLOCA O SIMBOLO NA POSICAO */
                break;
            }
            else
                printf("Invalido!");

        }

    }
    else
    {
        while(1)
        {
            printf("\n\nLinha: ");
            scanf(" %c", &c_linha);
            printf("Coluna: ");
            scanf(" %c", &c_coluna);

            fflush(stdin);

            linha = c_linha - '0';
            coluna = c_coluna - '0';

            --linha; --coluna; // --- pois index comeca em 0

            if((linha >= 0 && linha < dim) && (coluna >= 0 && coluna < dim) && tabuleiro[linha][coluna] == ' ')
            {
                tabuleiro[linha][coluna] = player.simbolo;
                break;
            }
            else
            {
                printf("Invalido!");
            }
        }

    }
}

//------------------------------------------------------------------------------

void inic_ptrTecladoNum(char** tabuleiro, int dim, char *ptr_casa[10])
{

    if( dim != 3 )
    {
        printf("\nErro fatal! inic_ptrTecladoNum com dimensoes diferente de 3\n");
        exit(1);
    }
    ptr_casa[0] = NULL; /* POSICAO 0 EH IGNORADA */
    ptr_casa[1] = &tabuleiro[2][0];
    ptr_casa[2] = &tabuleiro[2][1];
    ptr_casa[3] = &tabuleiro[2][2];

    ptr_casa[4] = &tabuleiro[1][0];
    ptr_casa[5] = &tabuleiro[1][1];
    ptr_casa[6] = &tabuleiro[1][2];

    ptr_casa[7] = &tabuleiro[0][0];
    ptr_casa[8] = &tabuleiro[0][1];
    ptr_casa[9] = &tabuleiro[0][2];
}

//------------------------------------------------------------------------------

int verificar_vitoria(char **tabuleiro, int sz, char c)
{
    int i, j;
    int sequencia;      // --- contador
    int quant_para_ganhar = sz;  // --- Quantidade de simbolos em sequencia para vitoria
    // board[3][3]:
    //    [0][0] | [0][1] | [0][2]
    //    -------+--------+-------
    //    [1][0] | [1][1] | [1][2]
    //    -------+--------+-------
    //    [2][0] | [2][1] | [2][2]

    // --- CHECA AS LINHAS
    sequencia = 0;
    for(i = 0; i < sz; i++)
    {
        for(j = 0; j < sz; j++)
        {
            if(tabuleiro[i][j] == c) ++sequencia;
            else sequencia = 0;

            if(sequencia == quant_para_ganhar) return 1;
        }

        sequencia = 0; // --- RESETA PRA CHECAR A PROXIMA LINHA
    }

    // --- CHECA AS COLUNAS
    sequencia = 0;
    for(j = 0; j < sz; j++)
    {
        for(i = 0; i < sz; i++)
        {
            if(tabuleiro[i][j] == c) ++sequencia;
            else sequencia = 0;

            if(sequencia == quant_para_ganhar) return 1;
        }

        sequencia = 0; // --- RESETA PARA CHECAR A PROXIMA COLUNA
    }

    // --- CHECA A DIAGONAL PRINCIPAL [ TOPO ESQUERDO - BASE DIREITA ]
    sequencia = 0;
    for(i = 0; i < sz; i++)
    {
        if(tabuleiro[i][i]  == c) ++sequencia;
        else sequencia = 0;
    }
    if(sequencia == quant_para_ganhar) return 1;

    // --- CHECA A DIAGONAL [ BASE ESQUERDA - TOPO DIREITO ]
    sequencia = 0;
    j = 0;
    for(i = sz-1; i >= 0; --i)
    {
        if(tabuleiro[i][j] == c) ++sequencia;
        else sequencia = 0;
        if(sequencia == quant_para_ganhar) return 1;

        ++j;
    }

    return 0;
}

//------------------------------------------------------------------------------


void mostrar(char **tabuleiro, int dim)
{
    int i, j, k;
    for(i = 0; i < dim; ++i)
    {
        for(j = 0; j < dim; ++j)
        {
            printf(" %c %c", tabuleiro[i][j], j== dim-1 ? '\n' : '|');
        }
        for(k = 0; k < dim; ++k) /* PRINTA AS DIVISORIAS */
        {
            if(i != dim-1)
                printf("%s", k == dim-1 ? "---\n" : "---|");
        }
    }

}

//------------------------------------------------------------------------------

void ordenar_ranking(tRanking *ranking, size_t sz)
{
    int i, j;
    tRanking temp;

    if(sz <= 1) return;

    for(i = 0; i < sz; ++i)
    {
        for(j = 0; j < sz; ++j)
        {
            if(ranking[i].score > ranking[j].score)
            {
                temp = ranking[i];
                ranking[i] = ranking[j];
                ranking[j] = temp;
            }
        }
    }
}

//------------------------------------------------------------------------------

void Jogar_vs_IA()
{
    tRanking ranking; //--- Possibilidade de salvar score
    tPlayer jogador[2];
    size_t atual; //--- INDEX DO JOGADOR DA VEZ

    size_t dim  = 3;
    char **tabuleiro;

    int ganhou , empatou, FimDaPartida, GameOver; //--- TRUE OU FALSE
    unsigned short turn;    //--- RODADA
    Tutorial( dim );

    inic_players( jogador ); //--- Inicializa com valor padrao os players
    escolher_nicks(jogador[0].nick, jogador[1].nick, 1);   //--- 1 de bool_IA

    do{ /** Enquanto a IA nao ganhar e o player quiser jogar mais **/

        tabuleiro = gerar_tabuleiro( dim );
        FimDaPartida = 0;
        GameOver = 0;
        turn = 1;
        atual = caraOuCoroa( jogador[0].nick, jogador[1].nick );

        do{ /** Enquanto a partida estiver em andamento **/

            if(atual == 1)  //--- SE FOR A VEZ DA IA
            {
                limpar_tela(); //--- VEZ DA IA NAO TEM INTERFACE
                IA_Joga( jogador, tabuleiro, dim );
            }
            else
            {
                IA_Game_Interface(jogador, tabuleiro, dim); //--- Monstra interface com score
                Player_Joga(jogador[atual], tabuleiro, dim);
            }
            ++jogador[atual].qt_jogadas_totais;

            /* VERIFICA FIM DE JOGO */
            ganhou = verificar_vitoria( tabuleiro, dim, jogador[atual].simbolo );
            empatou = ( (!ganhou) && turn == dim*dim );

            if(ganhou)
            {
                if(atual == 1) GameOver =  1;   //--- Se a IA ganhou = GAME OVER.

                Interface_ganhador( jogador[atual], tabuleiro, dim );
                pause();

                ++jogador[atual].vitorias;
                jogador[atual].score += 2500; //--- VENCEDOR GANHA +2500 PONTOS

                FimDaPartida = 1;

            }
            else if(empatou)
            {
                Interface_empate( jogador, tabuleiro, dim );
                pause();

                ++jogador[0].empates;
                jogador[0].score += 500;

                jogador[1].score += 500;
                ++jogador[1].empates;

                FimDaPartida = 1;

            }
            else //--- PARTIDA EM ANDAMENTO
            {
                atual = !atual; //--- TROCA DE VEZ
                ++turn;
            }

        }while(!FimDaPartida);

        freeBoard(tabuleiro, dim);   //--- Desaloca o tabuleiro

    }while((!GameOver) && jogar_mais());

      /*** FIM DE JOGO ***/

    limpar_tela();
    printf("****************************************\n");
    printf("              GAME OVER                 \n");
    printf("****************************************\n\n");

    mostrar_status( jogador );

    printf("\n\nSeu score foi %0.f", jogador[0].score);
    if(perguntar("\nQuer salvar score [S/N] : "))
    {
        strcpy(ranking.nick, jogador[0].nick);
        ranking.score = jogador[0].score;

        if(salvar_ranking(ranking)) //--- Retorna um boolean de sucesso
        {
            printf("\nSCORE SALVO!\n");
        }
        else
        {
            printf("\nERRO AO SALVAR SCORE!\n");
        }
    }

    pause();

}

//------------------------------------------------------------------------------

void Jogar_vs_Player()
{
    tPlayer jogador[2];
    size_t atual; //--- INDEX DO JOGADOR DA VEZ

    int ganhou , empatou, FimDaPartida, GameOver; //--- TRUE OU FALSE
    unsigned short turn, serie;

    size_t dim  = 3; //--- Coloca no maximo 9 pra nao complicar sua vida
    char **tabuleiro;

    Tutorial( dim );

    inic_players( jogador ); //--- Inicializa com valor padrao os players
    escolher_nicks(jogador[0].nick, jogador[1].nick, 0);   //--- 0 de bool_IA

    serie = 1;  //--- Inicializa como uma melhor de 1

    do{ /** Enquanto a serie nao acabar ou quiser jogar mais **/

        tabuleiro = gerar_tabuleiro( dim );
        FimDaPartida = 0;
        GameOver = 0;
        turn = 1;
        atual = caraOuCoroa( jogador[0].nick, jogador[1].nick );

        do{ /** Enquanto a partida estiver em andamento **/

            PvP_Game_Interface(jogador, serie, tabuleiro, dim);

            Player_Joga( jogador[atual], tabuleiro, dim ); //--- COLOCA SIMBOLO NA POSICAO VALIDA
            ++jogador[atual].qt_jogadas_totais;

            /* VERIFICA FIM DE JOGO */
            ganhou = verificar_vitoria( tabuleiro, dim, jogador[atual].simbolo );
            empatou = ( (!ganhou) && turn == dim*dim );

            if(ganhou)
            {
                Interface_ganhador( jogador[atual], tabuleiro, dim );
                ++jogador[atual].vitorias;

                FimDaPartida = 1;

            }
            else if(empatou)
            {
                Interface_empate( jogador, tabuleiro, dim );

                ++jogador[0].empates;
                ++jogador[1].empates;

                FimDaPartida = 1;

            }
            else //--- PARTIDA EM ANDAMENTO
            {
                atual = !atual; //--- TROCA DE VEZ
                ++turn;
            }

        }while(!FimDaPartida);

        freeBoard(tabuleiro, dim);   //--- Desaloca o tabuleiro

        if(jogador[0].vitorias  > serie/2 || jogador[1].vitorias > serie/2) //--- Fim da serie
        {
            if(jogar_mais())
                serie += 2;
            else
                GameOver = 1;
        }

    }while(!GameOver);

    /*** FIM DE JOGO ***/

    limpar_tela();
    if(jogador[0].vitorias == jogador[1].vitorias)
    {
        printf("****************************************\n");
        printf("               EMPATOU                  \n");
        printf("****************************************\n\n");
    }
    else
    {
        printf("******************************************\n");
        printf("WINNER\t%15s%15s\n", jogador[0].vitorias > jogador[1].vitorias ? jogador[0].nick :jogador[1].nick, "WINNER" );
        printf("******************************************\n\n");
    }

    mostrar_status( jogador );
    pause();

}

//------------------------------------------------------------------------------
