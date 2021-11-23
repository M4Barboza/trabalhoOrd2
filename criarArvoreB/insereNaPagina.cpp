#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insere_na_pagina (int chave, int filho_d,PAGINA *pag){
    int i = pag->contachaves;
    while(i > 0 && chave < pag->chave[i-1]){
        pag->chave[i] = pag->chave[i-1];
        pag->filho[i+1] = pag->filho[i];
        i--;
    }
    pag->contachaves++;
    pag->chave[i] = chave;
    pag->filho[i+1] = filho_d;
}