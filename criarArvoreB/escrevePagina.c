#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void escreve_pagina(int rrn, PAG pag){
    FILE *arq;   
    arq = fopen("Btree.dat","r+");
    int byteoffset = rrn*sizeof(pag); 
    fseek(arq,byteoffset,SEEK_SET);
    fwrite(&pag,sizeof(pag),1,arq);
}