#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../defines.h"

int Inicializa_pagina(PAG *pag){

    pag->quantidadeDeChaves = 0;

    for(int i=0;i<=qtdDeCampos-1;i++){
        pag->chave[i] = -1;
        pag->filhos[i] = -1;
    }
    pag->filhos[qtdDeCampos] = -1;
}