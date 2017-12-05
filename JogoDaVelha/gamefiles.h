#ifndef GAMEFILES_H_INCLUDED
#define GAMEFILES_H_INCLUDED

#define RANKING_DATA_FILE "ranking.DAT"

//------------------------------------------------------------------------------

typedef struct{
    char nick[16];
    double score;
}tRanking;

//------------------------------------------------------------------------------

int salvar_ranking(tRanking ranking);

//------------------------------------------------------------------------------

int coletar_ranking(tRanking **source);

//------------------------------------------------------------------------------

#endif // GAMEFILES_H_INCLUDED
