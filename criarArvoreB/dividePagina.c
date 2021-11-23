#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void divide(int chave,int filho_d,PAGINA *pag, int *chave_pro,int *filho_d_pro,PAGINA *novapag){
    PAGINA pagaux;
    pagaux = copiar_pag(pag);//copie PAG para PAGAUX  
    /* Insira CHAVE e FILHO_D nos lugares apropriados em PAGAUX */
    int i = ordem-1;
    while(chave < pagaux.chave[i-1] && i>0){
        pagaux.chave[i] = pagaux.chave[i-1];
        pagaux.filho[i+1] = pagaux.filho[i];
        i--;
    }
    pagaux.chave[i] = chave;
    pagaux.filho[i+1] = filho_d;
    int meio = (ordem)/2;
    int rrn;
    *filho_d_pro = busca_na_pagina(chave,*novapag,&rrn); //faça FILHO_D_PRO receber o RRN que a NOVAPAG terá no arquivo árvore-b -> socorro !? :(
    *chave_pro = pagaux.chave[meio];
    /* Copie as chaves e ponteiros que vêm depois de CHAVE_PRO para NOVAPAG */
    inicializa_pagina(novapag);
    i = meio+1;
    while(i<ordem){
        novapag->chave[novapag->contachaves] = pagaux.chave[i];
        novapag->filho[novapag->contachaves] = pagaux.filho[i];
        novapag->contachaves++;
        i++;
    }
    novapag->filho[novapag->contachaves] = pagaux.filho[i];
}