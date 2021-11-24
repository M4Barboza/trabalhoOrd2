#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

#include "insere.c"
#include "busca.c"



void criarArvoreB(char Arquivo[]){

    FILE *entrada;
    FILE *Btree;
    char chave;
    int rrn_Pagina_Atual,chave,aux,filho_d_pro,chave_promovida,rrn;

    if ((entrada = fopen(Arquivo, "r")) == NULL){

        fprintf(stderr, "Erro ao abrir o arquivo %s\n", Arquivo);
        return EXIT_FAILURE;
    }  
    if ((Btree = fopen("Btree.dat","r+")) == NULL){

        fprintf(stderr, "Erro ao abrir o arquivo Btree\n");
        return EXIT_FAILURE;
    }  

    rrn_Pagina_Atual = 0;
    inicializa_pagina(&novaPagina);
    escreve_pagina(rrn_Pagina_Atual,novaPagina);

    fseek(Btree,0,SEEK_SET);
    fread(&chave,sizeof(int),1,Btree);

    while(fscanf(Btree,"%d|",&aux)!= -1){
        if(insere(rrn_Pagina_Atual,chave,&filho_d_pro,&chave_promovida, novaPagina) == ComPromocao){
            inicializa_pagina(&novaPagina);
            novaPagina.chave[0] = chave_promovida;
            novaPagina.filhos[0] = rrn_Pagina_Atual;
            novaPagina.filhos[1] = filho_d_pro;
            escreve_pagina(rrn_Pagina_Atual,novaPagina);
            rrn = RRN_novapag();
            rrn_Pagina_Atual = rrn; 
        }
        fseek(Btree,sizeof(int),SEEK_CUR);
        fread(&chave,sizeof(int),1,Btree);
    }
    fwrite(&rrn_Pagina_Atual,sizeof(int),1,Btree);
    fclose(Btree);
   
    

}