#include <stdio.h>
#define MAXCHAVE 5


typedef struct {
    
    int quantidadeDeChaves;
    char chave[MAXCHAVE];
    int filhos[MAXCHAVE + 1];
} PAG;



void insereChave(int RRN_Pag_Atual, int chave, int filho_pag_PRO , int chave_promovida){

    int result;
    int filho_pag_PRO2;
    int chave_promovida2;

    if (RRN_Pag_Atual == NULL)
    {
        chave_promovida = chave;
        filho_pag_PRO = NULL;
        //return PROMOCAO;
    }
    else
    {

        // PAG recebe informações da RRN_Pag_Atual
        // result = busca(chave, PAG, posicaoChave)
        if (result)
        {
            printf("Chave duplicada");
            //return ERRO;
        }
        

    }
    
    int retorno = insereChave(PAG.filhos[posicaoChave],chave, filho_pag_PRO2 , chave_promovida)

    if (retorno == Sem_Promocao || retorno == ERRO)
    {
        return retorno;
    }
    

}