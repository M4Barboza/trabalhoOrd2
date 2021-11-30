#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../defines.h"


int RRN_novapag(){
    FILE *Btree;
    Btree = fopen("Btree.dat","r+b");
    int tamanhopag = sizeof(PAG);
    int tamanhocab = sizeof(int);
    fseek(Btree,0,SEEK_END);
    int byteoffset = ftell(Btree);
    fclose(Btree);

    return (byteoffset - tamanhocab)/tamanhopag;
}

