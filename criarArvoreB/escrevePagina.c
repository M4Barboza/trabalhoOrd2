void escreve_pagina(int rrn, PAG pag){
    FILE *arq;   
    arq = fopen("Btree.dat","r+");
    int byteoffset = rrn*sizeof(PAG); // ta certo ???
    fseek(arq,byteoffset,SEEK_SET);
    fwrite(&pag,sizeof(PAGINA),1,arq);
}