#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void insere_na_pagina (int chave, int filho_direita,PAG *pag){

    int i = pag->quantidadeDeChaves;

    while(i > 0 && chave < pag->chave[i-1]){
        pag->chave[i] = pag->chave[i-1];
        pag->filhos[i+1] = pag->filhos[i];
        i--;
    }
    
    pag->quantidadeDeChaves++;
    pag->chave[i] = chave;
    pag->filhos[i+1] = filho_direita;
}