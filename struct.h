#include "defines.h"

typedef struct {
    
    int quantidadeDeChaves;
    char chave[MAXCHAVE];
    int filhos[MAXCHAVE + 1];
} PAG;
