#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void inicializa_pagina(PAG *pag){

    pag->quantidadeDeChaves = 0;

    for(int i=0;i<=qtdDeCampos-1;i++){
        pag->chave[i] = NULL;
        pag->filhos[i] = NULL;
    }
    pag->filhos[qtdDeCampos] = NULL;
}