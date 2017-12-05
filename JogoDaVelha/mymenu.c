#include "interface.h"
#include "mymenu.h"
#include "myfunc.h"

//------------------------------------------------------------------------------

int Criar_Menu(char **menu, size_t menu_sz, char *title)
{
    size_t idx_selected = 0;
    int key = 0;
    int i;
    while(1)
    {
        limpar_tela();          // --- Atualiza a tela a cada loop
        printf("%s\n", title);

        //---- PRINTA O MENU
        for(i = 0; i < menu_sz; i++)
        {
            printf("%s", menu[i]);
            if(i == idx_selected)
                printf("   <-");
            printf("\n");
        }
        //  ---

        while(1) // --- VERIFICA POR TECLAS PRESSIONADAS
        {
            key = getch();

            if(key == 13)
            {
                fflush(stdin);
                return idx_selected;

            }
            else if(key == 224)
            {
                switch(getch())
                {
                    case 72:  // --- UP ARROW
                        --idx_selected;
                        if(idx_selected == -1)
                            idx_selected = menu_sz -1;
                        break;

                    case 80: // --- DOWN ARROW
                        ++idx_selected;
                        if(idx_selected == menu_sz)
                            idx_selected = 0;
                        break;
                    default:
                        continue;

                }
            }else continue;

           break;

        }
        dormir(100);
    }

}

//------------------------------------------------------------------------------

int Criar_Menu_Basico(char **menu, int sz, char *title)
{
    char c_escolha = 0;
    size_t idx_escolhido = 0;
    int i;

    if(strcmp(title, "")) // --- SE EXISTE TITULO
        printf("%s\n", title);

    for(i = 0; i < sz; i++)
        printf("%d - %s\n", i+1, menu[i]);

    while(1)
    {
        printf("\nOpcao: ");
        scanf(" %c", &c_escolha);
        fflush(stdin);

        idx_escolhido = c_escolha - '0';
        --idx_escolhido;    //--- Pois Retorna Um Index

        if(idx_escolhido >= 0 && idx_escolhido < sz) //--- INDEX ESCOLHIDO VALIDO
            return idx_escolhido;
        else
            printf("Invalido!\n");

    }
}

//------------------------------------------------------------------------------

void home()
{
    size_t menu_sz = 4;
    char* menu[4] = {"Jogar", "Ranking","Creditos", "Sair"};
    size_t idx_selected;

    do
    {
        //limpar_tela();
        idx_selected = Criar_Menu(menu, menu_sz, "MENU PRINCIPAL\n");

        switch(idx_selected)
        {
            case 0: limpar_tela();
            escolher_oponente();
            break;

            case 1: limpar_tela();
            ranking();
            break;

            case 2: limpar_tela();
            creditos();
            break;
        }

    }while(idx_selected != 3);

}

//------------------------------------------------------------------------------

void escolher_oponente()
{
    size_t menu_sz = 3;
    char* menu[3] = {"Player vs Player", "Player vs IA", "Voltar"};
    size_t idx = 0;

    while(1)
    {
        //limpar_tela();
        idx = Criar_Menu(menu, menu_sz, "Vamos Jogar\n");

        switch(idx)
        {
            case 0: limpar_tela();
                Jogar_vs_Player();
                break;

            case 1: limpar_tela();
                Jogar_vs_IA();
                break;

            case 2:
                return;
        }

    }
}

//------------------------------------------------------------------------------
