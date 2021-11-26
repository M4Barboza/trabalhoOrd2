#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../defines.h"


void le_pagina(int rrn, PAG *pagina){
    FILE *arq;   
    arq=fopen("Btree.dat","r+");
    int byteoffset = rrn*sizeof(pagina);
    fseek(arq,byteoffset,SEEK_SET);
    fread(pagina,sizeof(pagina),1,arq);
}




