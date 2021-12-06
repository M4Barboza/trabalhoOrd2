#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"

#include "criarArvoreB/btree.c"

int main(int argc, char *argv[])
{

    if (argc == 3 && strcmp(argv[1], "-c") == 0)
    {

        printf("criacao da arvore B ativada no arquivo = %s\n", argv[2]);
        gerenciador(argv[2]);
    }
    else if (argc == 3 && strcmp(argv[1], "-p") == 0)
    {

        printf("Impressso da arvore-B do arquivo = %s\n", argv[2]);
        impressaoArvoreB(argv[2]);
    }
    else if (argc == 2 && strcmp(argv[1], "-k") == 0)
    {

        printf("impressao das chaves em ordem crescente do arquivo %s\n", argv[2]);
        impressaoChavesOrdemCrescente(argv[2]);
    }
    else
    {

        fprintf(stderr, "Argumentos incorretos!\n");
        fprintf(stderr, "Modo de uso:\n");
        fprintf(stderr, "$ %s (-c|-k) nome_arquivo\n", argv[0]);
        fprintf(stderr, "$ %s -p\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return 0;
}
