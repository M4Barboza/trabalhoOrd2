#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAVE 5
#define erro "erro"
#define encontrado 1
#define naoEncontrado 0
#define ComPromocao 2
#define semPromocao 3
#define delimitador "|"

int insere(int rrn_Pagina_Atual,char chave,int  *filho_d_pro,int *chave_pro){
    PAG pagina,novapag;
    int result = 0;
    int pos = 0;

    if(rrn_Pagina_Atual== -1 || rrn_Pagina_Atual== NULL){
        *chave_pro = chave;
        *filho_d_pro = -1;
        return erro; 
    }
    else{
        le_pagina(rrn_Pagina_Atual, &pagina);
        result = busca_na_pagina(chave, pagina,&pos);
    }

    if(result == encontrado){
        printf("\nChave duplicada");
        return erro;
    }

    int rrn_pro,chv_pro; //n sei ta certo isso !!!
    int retorno = insere(pagina.filhos[pos],chave,&rrn_pro,&chv_pro);

    if(rrn_Pagina_Atual == -1/* NULL */){
        *chave_pro = chave;
        *filho_d_pro = -1/* NULL */;
        return ComPromocao;
    }
    else{
        le_pagina(rrn_Pagina_Atual,&pagina);//leia a página armazenada em RRN_ATUAL para PAG -> função que lê
        result = busca_na_pagina(chave,pagina,&pos);
    }

    if(result == encontrado){
        printf("\nchave duplicada!");
        return erro;
    }

    retorno = insere(pagina.filhos[pos],chave,&rrn_pro,&chv_pro);

    if(retorno == ComPromocao || erro){
        return retorno;
    }
    else{//houve promoção da inserção
        if(pagina.quantidadeDeChaves < ordem-1){
            insere_na_pagina(chv_pro,rrn_pro,&pagina);
            escreve_pagina(rrn_Pagina_Atual,pagina);
            return semPromocao;
        }
        else{
            divide(chv_pro,rrn_pro,&pagina,chave_pro,filho_d_pro,&novapag);
            escreve_pagina(rrn_Pagina_Atual,pagina);
            escreve_pagina(filho_d_pro,novapag);
            return ComPromocao;
        }
    }
}




