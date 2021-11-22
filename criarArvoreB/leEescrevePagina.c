
void le_pagina(int rrn,PAGINA *pag){
    FILE *arq;   
    arq=fopen("Btree.dat","r+");
    int byteoffset = rrn*sizeof(PAGINA); // ta certo ???
    fseek(arq,byteoffset,SEEK_SET);
    fread(pag,sizeof(PAGINA),1,arq);
}

void escreve_pagina(int rrn, PAGINA pag){
    FILE *arq;   
    arq = fopen("Btree.dat","r+");
    int byteoffset = rrn*sizeof(PAGINA); // ta certo ???
    fseek(arq,byteoffset,SEEK_SET);
    fwrite(&pag,sizeof(PAGINA),1,arq);
}