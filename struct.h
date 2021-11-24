#define MAXCHAVE 4
#define encontrado 1
#define naoEncontrado 0
#define qtdDeCampos 4
#define erro "erro"
#define ComPromocao 2
#define semPromocao 3
#define delimitador "|"

typedef struct {
    
    int quantidadeDeChaves;
    char chave[MAXCHAVE];
    int filhos[MAXCHAVE + 1];
} PAG;
