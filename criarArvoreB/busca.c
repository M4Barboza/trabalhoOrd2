#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define encontrado 1
#define naoEncontrado 0

int busca (int rrn,int chave,int  *rrn_encontrado,int *pos_encontrada){
    if(rrn < 0){
        return naoEncontrado;
    }
    PAGINA pag;
    pag.contachaves =  rrn;
    int pos = 0;
    int result = busca_na_pagina(chave, pag, &pos);
    if(result == encontrado){
        *rrn_encontrado = rrn;  /* rrn da página que contém a chave */
        *pos_encontrada = pos;  /* posição da chave na página*/
        return encontrado;
    }
    else{ /* siga o ponteiro para a próxima página da busca */
        return(busca(pag.filho[pos],chave,rrn_encontrado,pos_encontrada));
    }
}