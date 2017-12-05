#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "gamefiles.h"
#include "interface.h"
#include "tictactoe.h"
#include "myfunc.h"

//------------------------------------------------------------------------------

void Tutorial(int dim)
{

    printf("###########################\n");
    printf("     * JOGO DA VELHA *     \n");
    printf("###########################\n\n");

    printf("Instrucoes: Manual para dois jogadores.\n");
    printf(" - Jogador 1 vai ser o caracter \"X\"\n");
    printf(" - Jogador 2 vai ser o caracter \"O\"\n\n");

    printf("Condicao de vitoria:\n");
    printf(" - Oculpar caracteres iguais em linha, coluna ou diagonal\n\n");

    printf("Condicao de empate:\n");
    printf(" - Todas as posicoes preenchidas sem ter havido vitoria\n\n");

    printf("Como jogar:\n");
    printf(" - Escolha a posicao assim como no desenho\n\n");

    if(dim == 3)
    {
        printf("   |   |   \n");
        printf(" 7 | 8 | 9 \n");
        printf("---|---|---\n");
        printf(" 4 | 5 | 6 \n");
        printf("---|---|---\n");
        printf(" 1 | 2 | 3 \n");
        printf("   |   |   \n");
    }
    pause();
    limpar_tela();
}

//------------------------------------------------------------------------------

int caraOuCoroa(char *nome1, char *nome2)
{
    srand(time(NULL));
    size_t res = rand() % 2; /*CARA = 0 COROA = 1*/

    printf("\n\t%s = CARA   <-->    ", nome1);
    printf("%s = COROA\n", nome2);

    if(res)
        printf("\n\n\t     * Deu COROA, %s Comeca! *\n\n", nome2);
    else
        printf("\n\n\t     * Deu CARA, %s Comeca! *\n\n", nome1);

    pause();

    return res;
}

//------------------------------------------------------------------------------

void escolher_nicks(char nick1[MAX_NICK], char nick2[MAX_NICK], int bool_IA)
{
    printf("Para ser um lenda, antes voce tem que escolher um nick!\n");
    printf("Como podemos chamar voce?\n\n");
    printf("[AVISO] Nao eh permitido: \n");
    printf(" - Espacos em branco no nick\n");
    printf(" - Nick com mais de 15 caracteres\n");
    printf(" - Player 1 e Player 2 com nomes iguais\n\n");

    if(bool_IA)
    {
        strcpy(nick2, IA_NAME);
        while(1) // IA e PLAYER NAO PODEM TER O MESMO NICK
        {
            printf("\nPlayer 1, nick: ");
            scanf("%15s", nick1);
            fflush(stdin);

            if(strcmp(nick1, nick2) == 0)
                printf("Nao permitido nome igual a IA!\n");
            else
                break;
        }

    }
    else
    {
        printf("Player 1, nick: ");
        scanf("%15s", nick1);
        fflush(stdin);

        while(1) // PLAYER 1 E PLAYER 2 NAO PODEM TER O MESMO NICK
        {
            printf("\nPlayer 2, nick: ");
            scanf("%15s", nick2);
            fflush(stdin);

            if(strcmp(nick1, nick2) == 0)
                printf("Nao permitido nomes iguais!\n");
            else
                break;
        }
    }

}

//------------------------------------------------------------------------------

int jogar_mais()
{
    if(perguntar("\n\nQuer Jogar mais [S/N] : "))
        return 1;
    return 0;
}

//------------------------------------------------------------------------------

int perguntar(char *sentence)
{
    char resposta = 0;
    int tentavias = 0;

    while(tentavias < 3) /* TEM 3 CHANCES PARA COLOCAR UM INPUT VALIDO */
    {
        printf("%s", sentence);
        scanf(" %c", &resposta);
        fflush(stdin);

        switch(resposta)
        {
            case 's': case 'S': return 1;
            case 'n': case 'N': return 0;

            default:
                printf("Nao Entendi!");
                ++tentavias;
        }

    }

    printf("\n\nVou levar isso como um nao :(");
    return 0;

}

//------------------------------------------------------------------------------

void IA_Game_Interface(tPlayer player[2], char **tabuleiro, size_t dim)
{
    limpar_tela();
    printf("Jogo Da Velha\n\n");
    printf("Score:\n - %s: %.0f\n - %s: %.0f\n\n", player[0].nick, player[0].score, player[1].nick, player[1].score);
    mostrar(tabuleiro, dim);
}

//------------------------------------------------------------------------------

void PvP_Game_Interface(tPlayer player[2], unsigned short serie, char **tabuleiro, size_t dim)
{
    limpar_tela();
    printf("Jogo Da Velha\n\n");
    printf("%s: %d\n", player[0].nick, player[0].vitorias);
    printf("%s: %d\n\n", player[1].nick, player[1].vitorias);
    printf("Melhor de %hu\n\n", serie);
    mostrar(tabuleiro, dim);
}

//------------------------------------------------------------------------------

void Interface_ganhador(tPlayer player, char **tabuleiro, size_t dim)
{
    limpar_tela();
    printf("Jogo da velha\n\n");
    mostrar(tabuleiro, dim);
    printf("\n\nTEMOS UM VENCEDOR!");
    printf("\n\n%s Ganhou.\n\n", player.nick);
}

//------------------------------------------------------------------------------

void Interface_empate(tPlayer player[2], char **tabuleiro, size_t dim)
{
    limpar_tela();
    printf("Jogo da velha\n\n");
    mostrar(tabuleiro, dim);
    printf("\n\nEMPATE!");
    printf("\n\n%s e %s Empataram.\n\n", player[0].nick, player[1].nick);
}

//------------------------------------------------------------------------------

void mostrar_status(tPlayer player[2])
{//VOU COLOCAR UM ARQUIVO AKI COM UMAS IMAGENS DE EMPATE OU VITORIA

    printf("STATUS:\n");
    printf(" - Vitorias player 1: %-2d\n", player[0].vitorias);
    printf(" - Quant. de jogadas: %-2d\n", player[0].qt_jogadas_totais);
    printf("\n");
    printf(" - Vitorias player 2: %-2d\n", player[1].vitorias);
    printf(" - Quant. de jogadas: %-2d\n", player[1].qt_jogadas_totais);
    printf("\n");
    printf(" - Numero de empates: %-2d\n", player[0].empates); /* TANTO FAZ PLAYER 1 OU PLAYER 2 */
    printf(" - TOTAL DE PARTIDAS: %-2d\n", player[0].vitorias + player[1].vitorias + player[0].empates);
    printf("----------------------------------------\n");

}

//------------------------------------------------------------------------------

void mostrar_ranking(tRanking* ranking, int n_elem)
{
    int i;
    // --- PRINTA OS SCORES ---
    if(n_elem > 0)
    {
        printf("\n\n   RANKING DE JOGADORES\n\n\n");
        printf("   NICK\t\t      SCORE\n\n");

        for(i = 0; i < n_elem; ++i)
            printf("%2d. %-17s %-.0f\n", i+1, ranking[i].nick, ranking[i].score);
    }
    else
    {
        printf("NENHUM SCORE SALVO\n\n");
    }

}

//------------------------------------------------------------------------------

void ranking()
{
    tRanking *ranking = NULL;
    int n_elem = 0;

    n_elem = coletar_ranking( &ranking );

    ordenar_ranking(ranking, n_elem);

    mostrar_ranking(ranking, n_elem);

    pause();
    free(ranking);
}

//------------------------------------------------------------------------------

void creditos()
{
    printf("Creditos\n\n");

    printf("Programa criado por:\n\n");
    printf(" - Caio Vitor\n");
    printf(" - Emanuel Honorio\n");
    printf(" - Felipe Bento\n");
    printf(" - Joao Otavio\n");
    printf(" - Rafael Tobit\n");

    pause();

}
