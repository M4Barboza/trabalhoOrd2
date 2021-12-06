#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../defines.h"

typedef struct
{

    int quantidadeDeChaves;
    int chave[MAXCHAVE];
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

int busca_na_pagina(int chave, PAG PAG, int *posicaoChave)
{
    int i = 0;
    while ((i < PAG.quantidadeDeChaves) && (chave > PAG.chave[i]))
    {
        i++;
    }
    *posicaoChave = i;
    if ((*posicaoChave < PAG.quantidadeDeChaves) && (chave == PAG.chave[*posicaoChave]))
    {
        return encontrado;
    }
    else
    {
        return naoEncontrado;
    }
}

int busca(int rrn, int chave, int *rrn_encontrado, int *pos_encontrada)
{
    PAG pag;

    if (rrn < 0)
    {
        return naoEncontrado;
    }
    le_pagina(rrn, &pag);
    int pos = 0;
    int result = busca_na_pagina(chave, pag, &pos);

    if (result == encontrado)
    {

        *rrn_encontrado = rrn;
        *pos_encontrada = pos;
        return encontrado;
    }
    else
        return (busca(pag.filhos[pos], chave, rrn_encontrado, pos_encontrada));
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

int insere(int rrn_Pagina_Atual, int chave, int *pagina_filha_da_direita, int *chave_promovida)
{

    PAG pagina, novapag;
    int result;
    int PosicaoChave;
    int pagina_filha_da_direita2;
    int chave_promovida2;

    if (rrn_Pagina_Atual == -1)
    {
        *chave_promovida = chave;
        *pagina_filha_da_direita = -1;
        return ComPromocao;
    }
    else
    {
        le_pagina(rrn_Pagina_Atual, &pagina);
        result = busca_na_pagina(chave, pagina, &PosicaoChave);
    }

    if (result == encontrado)
    {
        printf("\nChave duplicada");
        return erro;
    }
    printf("%i", chave);
    int retorno = insere(pagina.filhos[PosicaoChave], chave, &pagina_filha_da_direita2, &chave_promovida2); // Não deu falha de segmentação aqui

    if (retorno == semPromocao || retorno == erro)
    {

        return retorno;
    }
    else /*Teve promoção*/
    {

        if (pagina.quantidadeDeChaves <= qtdDeCampos - 1)
        {
            insere_na_pagina(chave_promovida2, pagina_filha_da_direita2, &pagina); // talvez usar for e não uma funcao
            escreve_pagina(rrn_Pagina_Atual, pagina);
            return semPromocao;
        }
        else
        {
            divide(chave_promovida2, pagina_filha_da_direita2, &pagina, chave_promovida, pagina_filha_da_direita, &novapag);
            escreve_pagina(rrn_Pagina_Atual, pagina);
            escreve_pagina(*pagina_filha_da_direita, novapag);
            return ComPromocao;
        }
    }
}

//--------------FIM Operações Principais--------------------//

//--------------Funções Principais BTREE--------------------//

int gerenciador(char *Arquivo)
{
    FILE *entrada;
    PAG pagina, novaPagina;
    FILE *Btree;
    int rrn_Pagina_Atual, aux, filho_d_pro, chave_promovida, rrn;
    int chave, chave2, seek = 0;

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
        fwrite(&rrn_Pagina_Atual, sizeof(rrn_Pagina_Atual), 1, Btree);
        Inicializa_pagina(&novaPagina);
        escreve_pagina(rrn_Pagina_Atual, novaPagina);
    }

    /*  fscanf(entrada, "%i", &chave);
     int chaveTeste;
     while (fscanf(entrada, "%i |", &chaveTeste) != EOF) */

    for (int i = 0; i < pagina.quantidadeDeChaves; i++)
    {
        printf("Inserção de chave %d\n", pagina.chave[i]);
        if (insere(rrn_Pagina_Atual, chave, &filho_d_pro, &chave_promovida) == ComPromocao)
        {
            Inicializa_pagina(&novaPagina);
            novaPagina.quantidadeDeChaves = 1;
            novaPagina.chave[0] = chave_promovida;
            novaPagina.filhos[0] = rrn_Pagina_Atual;
            novaPagina.filhos[1] = filho_d_pro;
            escreve_pagina(rrn_Pagina_Atual, novaPagina);
            rrn = RRN_novapag();
            rrn_Pagina_Atual = rrn;
        }
        /*   if (chave >= 10)
          {
              seek += 3;
          }
          else
          {
              seek += 2;
          } */

        fseek(entrada, seek, SEEK_SET);
        // fscanf(entrada, "%i |", &chave);
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