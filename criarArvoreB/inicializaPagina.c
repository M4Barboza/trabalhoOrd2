#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define qtdDeCampos 4

void inicializa_pagina(PAGINA *pag){
    pag.quantidadeDeChaves = 0;
    for(int i=0;i<=qtdDeCampos-1;i++){
        pag->chave[i] = -1;
        pag->filho[i] = -1;//NULL;
    }
    pag->filho[qtdDeCampos] =  -1;//NULL;
}