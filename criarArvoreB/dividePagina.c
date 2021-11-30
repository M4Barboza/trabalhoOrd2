#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../defines.h"
//#include "../struct.h"

#include "./inicializaPagina.c"

PAG copiar_pag(PAG *pag){
    PAG pagina_auxiliar;
    pagina_auxiliar.quantidadeDeChaves = pag->quantidadeDeChaves;
    for(int i=0;i<MAXCHAVE-1;i++){
        pagina_auxiliar.chave[i] = pag->chave[i];
    }
    for(int i=0;i<MAXCHAVE;i++){
        pagina_auxiliar.filhos[i] = pag->filhos[i];
    }
    return pagina_auxiliar;
}

int divide(int chave,int filho_d,PAG *pag, int *chave_pro,int *filho_d_pro,PAG *novapag){
    PAG pagina_auxiliar;
    pagina_auxiliar = copiar_pag(pag); 
    
    int i = MAXCHAVE-1;
    while(chave < pagina_auxiliar.chave[i-1] && i>0){
        pagina_auxiliar.chave[i] = pagina_auxiliar.chave[i-1];
        pagina_auxiliar.filhos[i+1] = pagina_auxiliar.filhos[i];
        i--;
    }
    pagina_auxiliar.chave[i] = chave;
    pagina_auxiliar.filhos[i+1] = filho_d;
    int meio = (MAXCHAVE)/2;
    int rrn;
    *filho_d_pro = busca_na_pagina(chave,*novapag,&rrn); 
    *chave_pro = pagina_auxiliar.chave[meio];
   
    Inicializa_pagina(novapag);
    i = meio+1;
    while(i<MAXCHAVE){
        novapag->chave[novapag->quantidadeDeChaves] = pagina_auxiliar.chave[i];
        novapag->filhos[novapag->quantidadeDeChaves] = pagina_auxiliar.filhos[i];
        novapag->quantidadeDeChaves++;
        i++;
    }
    novapag->filhos[novapag->quantidadeDeChaves] = pagina_auxiliar.filhos[i];
}

