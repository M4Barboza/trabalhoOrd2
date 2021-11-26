#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../defines.h"


nt RRN_novapag(){
    FILE *arq;
    arq = fopen("Btree.dat","r+b");
    int tamanhopag = sizeof(PAG);
    int tamanhocab = sizeof(sizeof(int));
    fseek(arq,0,SEEK_END);
    int byteoffset = ftell(arq);
    //fread(&byteoffset,sizeof(int),1,arq); 
    fclose(arq);

    printf("NOVO RRRN %d",(byteoffset - tamanhocab)/tamanhopag);
    return (byteoffset - tamanhocab)/tamanhopag;
}

