#include <stdio.h>
#include <malloc.h>
#include "gamefiles.h"

//------------------------------------------------------------------------------

int salvar_ranking(tRanking ranking)
{
    int sucess = 0; //--- bool sucesso
    FILE *arquivo = fopen(RANKING_DATA_FILE, "ab");

    sucess = fwrite(&ranking, sizeof(tRanking), 1, arquivo);
    fclose(arquivo);

    return sucess;
}

//------------------------------------------------------------------------------

int coletar_ranking(tRanking **source)
{
    FILE *arquivo = NULL;
    *source = NULL;     // ---- Local aonde sera alocado o array de ranking's
    int n_elem = 0;     // ---- Numero de ranking's coletados ( Valor que a funcao retornara )
    unsigned short i;

    // --- COLETA OS DADOS DOS JOGADORES ---
    arquivo = fopen(RANKING_DATA_FILE, "rb");

    if(arquivo == NULL)
    {
        printf("Cannot Open file\n");
        return 0;
    }

    *source = (tRanking*) malloc(sizeof(tRanking));   //--- Aloca uma posicao
    n_elem = 1;                                 //--- Num. de elementos

    for(i = 0; ; ++i)
    {
        if(!fread(*source + i, sizeof(tRanking), 1, arquivo))    //--- Se nao conseguir ler
        {
            --n_elem;
            *source = (tRanking*) realloc(*source, sizeof(tRanking) * n_elem); //--- Desaloca a posicao
            break;
        }

        //--- Leitura com sucesso, aloca mais uma posiçao
        ++n_elem;
        *source = (tRanking*) realloc(*source, sizeof(tRanking) * n_elem);
    }

    fclose(arquivo);

    if(n_elem == 0) *source = NULL;

    return n_elem;  //--- Retorna o numero de elementos
}
