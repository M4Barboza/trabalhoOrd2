#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../defines.h"


int RRN_novapag(){
    FILE *arquivo;
    arquivo = fopen("Btree.dat","r+b");
    int tamanhopag = sizeof(PAG);
    int tamanhocab = sizeof(int);
    fseek(arquivo,0,SEEK_END);
    int byteoffset = ftell(arquivo);
    fclose(arquivo);

    return (byteoffset - tamanhocab)/tamanhopag;
}

