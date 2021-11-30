#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../defines.h"


void escreve_pagina(int rrn, PAG pag){
    FILE *Btree;   
    Btree = fopen("Btree.dat","r+");
    int byteoffset = rrn*sizeof(PAG); 
    fseek(Btree,byteoffset,SEEK_SET);
    fwrite(&pag,sizeof(pag),1,Btree);
}