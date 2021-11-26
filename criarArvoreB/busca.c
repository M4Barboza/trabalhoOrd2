#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../defines.h"
#include "../struct.h"


int busca_na_pagina(int chave,PAG *PAG,int *POS){
    int i=0;
    while((i < PAG->quantidadeDeChaves) && (chave > PAG->chave[i])){
        i++;
    }
    *POS = i;
    if((*POS < PAG->quantidadeDeChaves) && (chave == PAG->chave[*POS])){
        return encontrado;
    }
    else{
        return naoEncontrado;
    }
}

int busca(int rrn,int chave,int  *rrn_encontrado,int *pos_encontrada){
    PAG pag;

    if(rrn < 0){
        return naoEncontrado;
    }
    
    pag.quantidadeDeChaves =  rrn;
    int pos = 0;
    int result = busca_na_pagina(chave, &pag, &pos);

    if(result == encontrado){

        *rrn_encontrado = rrn;  
        *pos_encontrada = pos;
        return encontrado;
    }
    else return(busca(pag.filhos[pos],chave,rrn_encontrado,pos_encontrada));
        
    
}
