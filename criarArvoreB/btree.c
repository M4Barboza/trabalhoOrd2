#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../defines.h"

typedef struct
{

    int quantidadeDeChaves;
    char chave[MAXCHAVE];
    int filhos[MAXCHAVE + 1];
} PAG;

//--------------Funções Auxiliares--------------------//

void le_pagina(int rrn, PAG *pagina)
{
    FILE *arq;
    arq = fopen("Btree.dat", "r");
    int byteoffset = rrn * sizeof(pagina);
    fseek(arq, byteoffset, SEEK_SET);
    fread(pagina, sizeof(pagina), 1, arq);
}

int RRN_novapag()
{
    FILE *Btree;
    Btree = fopen("Btree.dat", "r+b");
    int tamanhopag = sizeof(PAG);
    int tamanhocab = sizeof(int);
    fseek(Btree, 0, SEEK_END);
    int byteoffset = ftell(Btree);
    fclose(Btree);

    return (byteoffset - tamanhocab) / tamanhopag;
}

void insere_na_pagina(int chave, int filho_direita, PAG *pag)
{

    int i = pag->quantidadeDeChaves;

    while (i > 0 && chave < pag->chave[i - 1])
    {
        pag->chave[i] = pag->chave[i - 1];
        pag->filhos[i + 1] = pag->filhos[i];
        i--;
    }

    pag->quantidadeDeChaves++;
    pag->chave[i] = chave;
    pag->filhos[i + 1] = filho_direita;
}

int Inicializa_pagina(PAG *pag)
{

    pag->quantidadeDeChaves = 0;

    for (int i = 0; i <= qtdDeCampos - 1; i++)
    {
        pag->chave[i] = ' ';
        pag->filhos[i] = -1;
    }
    pag->filhos[qtdDeCampos] = -1;
}

void escreve_pagina(int rrn, PAG pag)
{
    FILE *Btree;
    Btree = fopen("Btree.dat", "r+");
    int byteoffset = rrn * sizeof(PAG);
    fseek(Btree, byteoffset, SEEK_SET);
    fwrite(&pag, sizeof(pag), 1, Btree);
}

//--------------FIM Funções Auxiliares--------------------//

//--------------Operações Principais--------------------//

int busca_na_pagina(int chave, PAG PAG, int *POS)
{
    int i = 0;
    while ((i < PAG.quantidadeDeChaves) && (chave > PAG.chave[i]))
    {
        i++;
    }
    *POS = i;
    if ((*POS < PAG.quantidadeDeChaves) && (chave == PAG.chave[*POS]))
    {
        return encontrado;
    }
    else
    {
        return naoEncontrado;
    }
}

PAG copiar_pag(PAG *pag)
{
    PAG pagina_auxiliar;
    pagina_auxiliar.quantidadeDeChaves = pag->quantidadeDeChaves;
    for (int i = 0; i < MAXCHAVE - 1; i++)
    {
        pagina_auxiliar.chave[i] = pag->chave[i];
    }
    for (int i = 0; i < MAXCHAVE; i++)
    {
        pagina_auxiliar.filhos[i] = pag->filhos[i];
    }
    return pagina_auxiliar;
}

int divide(int chave, int filho_d, PAG *pag, int *chave_pro, int *filho_d_pro, PAG *novapag)
{
    PAG pagina_auxiliar;
    pagina_auxiliar = copiar_pag(pag);

    int i = MAXCHAVE - 1;
    while (chave < pagina_auxiliar.chave[i - 1] && i > 0)
    {
        pagina_auxiliar.chave[i] = pagina_auxiliar.chave[i - 1];
        pagina_auxiliar.filhos[i + 1] = pagina_auxiliar.filhos[i];
        i--;
    }
    pagina_auxiliar.chave[i] = chave;
    pagina_auxiliar.filhos[i + 1] = filho_d;
    int meio = (MAXCHAVE) / 2;
    int rrn;
    *filho_d_pro = busca_na_pagina(chave, *novapag, &rrn);
    *chave_pro = pagina_auxiliar.chave[meio];

    Inicializa_pagina(novapag);
    i = meio + 1;
    while (i < MAXCHAVE)
    {
        novapag->chave[novapag->quantidadeDeChaves] = pagina_auxiliar.chave[i];
        novapag->filhos[novapag->quantidadeDeChaves] = pagina_auxiliar.filhos[i];
        novapag->quantidadeDeChaves++;
        i++;
    }
    novapag->filhos[novapag->quantidadeDeChaves] = pagina_auxiliar.filhos[i];
}

int insere(int rrn_Pagina_Atual, char chave, int *pagina_filha_da_direita, int *chave_promovida)
{

    PAG pagina, novapag;
    int result = 0;
    int pos = 0;

    if (rrn_Pagina_Atual == -1)
    {
        *chave_promovida = chave;
        *pagina_filha_da_direita = -1;
        return ComPromocao;
    }
    else
    {
        le_pagina(rrn_Pagina_Atual, &pagina);
        result = busca_na_pagina(chave, pagina, &pos);
    }

    if (result == encontrado)
    {
        printf("\nChave duplicada");
        return erro;
    }

    int pagina_filha_da_direita2, chave_promovida2;
    int retorno = insere(pagina.filhos[pos], chave, &pagina_filha_da_direita2, &chave_promovida2);

    if (retorno == ComPromocao || retorno == erro)
    {

        return retorno;
    }
    else
    {

        if (pagina.quantidadeDeChaves <= qtdDeCampos - 1)
        {
            insere_na_pagina(chave_promovida2, pagina_filha_da_direita2, &pagina);
            escreve_pagina(rrn_Pagina_Atual, pagina);
            return semPromocao;
        }
        else
        {
            divide(chave_promovida2, pagina_filha_da_direita2, &pagina, chave_promovida, pagina_filha_da_direita, &novapag);
            escreve_pagina(rrn_Pagina_Atual, pagina);
            escreve_pagina(pagina_filha_da_direita, novapag);
            return ComPromocao;
        }
    }
}

//--------------FIM Operações Principais--------------------//

//--------------Funções Principais BTREE--------------------//

int gerenciador(char Arquivo[])
{

    FILE *entrada;
    PAG novaPagina;
    FILE *Btree;
    int rrn_Pagina_Atual, chave, aux, filho_d_pro, chave_promovida, rrn;

    if ((entrada = fopen(Arquivo, "r")) == NULL)
    {

        fprintf(stderr, "Erro ao abrir o arquivo %s\n", Arquivo);
        return EXIT_FAILURE;
    }

    if ((Btree = fopen("Btree.dat", "r+b")))
    {

        rrn_Pagina_Atual = fgetc(Btree);
    }
    else
    {

        Btree = fopen("Btree.dat", "w+b");
        rrn_Pagina_Atual = 0;
        fwrite(&rrn_Pagina_Atual, sizeof(int), 1, Btree);
        Inicializa_pagina(&novaPagina);
        escreve_pagina(rrn_Pagina_Atual, novaPagina);
    }

    fseek(Btree, 0, SEEK_SET);
    fread(&chave, sizeof(int), 1, Btree);

    while (fscanf(Btree, "%d|", &aux) != EOF)
    {
        if (insere(rrn_Pagina_Atual, chave, &filho_d_pro, &chave_promovida) == ComPromocao)
        {
            Inicializa_pagina(&novaPagina);
            novaPagina.chave[0] = chave_promovida;
            novaPagina.filhos[0] = rrn_Pagina_Atual;
            novaPagina.filhos[1] = filho_d_pro;
            escreve_pagina(rrn_Pagina_Atual, novaPagina);
            rrn = RRN_novapag();
            rrn_Pagina_Atual = rrn;
        }
        // fseek(Btree,sizeof(int),SEEK_CUR);
        fread(&chave, sizeof(int), 1, Btree);
    }
    fwrite(&rrn_Pagina_Atual, sizeof(int), 1, Btree);
    fclose(Btree);
}

void impressaoArvoreB(char *arquivo)
{
}

void impressaoChavesOrdemCrescente(char *arquivo)
{
}

//--------------FIM Funções Principais BTREE--------------------//
