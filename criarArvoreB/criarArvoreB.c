#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ComPromocao 2

#include "insere.c"

typedef struct {
    
    int quantidadeDeChaves;
    char chave[MAXCHAVE];
    int filhos[MAXCHAVE + 1];
} PAG;

void criarArvoreB(char Arquivo[]){

    FILE *entrada;
    FILE *Btree;
    char chave;
    PAG novaPagina;
    int raiz,chave,aux,filho_d_pro,chave_pro,rrn;

    if ((entrada = fopen(Arquivo, "r")) == NULL){

        fprintf(stderr, "Erro ao abrir o arquivo %s\n", Arquivo);
        return EXIT_FAILURE;
    }  
    if ((Btree = fopen("Btree.dat","r+")) == NULL){

        fprintf(stderr, "Erro ao abrir o arquivo Btree\n");
        return EXIT_FAILURE;
    }  

    raiz = 0;
    inicializa_pagina(&novaPagina);
    escreve_pagina(raiz,novaPagina);

    fseek(Btree,0,SEEK_SET);
    fread(&chave,sizeof(int),1,Btree);

    while(fscanf(Btree,"%d|",&aux)!= -1){
        if(insere(raiz,chave,&filho_d_pro,&chave_pro) == ComPromocao){
            inicializa_pagina(&novaPagina);
            novaPagina.chave[0] = chave_pro;
            novaPagina.filhos[0] = raiz;
            novaPagina.filhos[1] = filho_d_pro;
            escreve_pagina(raiz,novaPagina);
            rrn = RRN_novapag();
            raiz = rrn; 
        }
        fseek(Btree,sizeof(int),SEEK_CUR);
        fread(&chave,sizeof(int),1,Btree);
    }
    fwrite(&raiz,sizeof(int),1,Btree);
    fclose(Btree);
   
    

}