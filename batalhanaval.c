#include <stdio.h>
#include <stdlib.h>

#define TAB_SIZE 10
#define SHIP_SIZE 3

#define HABILIDADE_SIZE 5 // Matriz 5x5 para as áreas de efeito

// Inicializa o tabuleiro com água (0)
void inicializaTabuleiro(int tab[TAB_SIZE][TAB_SIZE]) {
    for (int i = 0; i < TAB_SIZE; i++)
        for (int j = 0; j < TAB_SIZE; j++)
            tab[i][j] = 0;
}

// Posiciona um navio no tabuleiro (horizontal, vertical, diagonal descendente ou ascendente)
int podeColocarNavio(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, int orientacao);
void posicionaNavio(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, int orientacao);

// Função para criar a matriz da habilidade Cone (5x5) - cone apontando para baixo
void criaHabilidadeCone(int cone[HABILIDADE_SIZE][HABILIDADE_SIZE]) {
    // Zera a matriz
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            // Condicional para formar um cone: no topo só o centro, depois vai expandindo para baixo
            int centro = HABILIDADE_SIZE / 2;
            // Regra: coluna j deve estar dentro do intervalo central que cresce com a linha i
            if (j >= centro - i && j <= centro + i)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Função para criar a matriz da habilidade Cruz (5x5)
void criaHabilidadeCruz(int cruz[HABILIDADE_SIZE][HABILIDADE_SIZE]) {
    int centro = HABILIDADE_SIZE / 2;
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            // Cruz: linha central e coluna central são 1, resto 0
            if (i == centro || j == centro)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Função para criar a matriz da habilidade Octaedro (5x5) - forma losango
void criaHabilidadeOctaedro(int octaedro[HABILIDADE_SIZE][HABILIDADE_SIZE]) {
    int centro = HABILIDADE_SIZE / 2;
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            // Losango: soma dos deslocamentos absolutos da linha e coluna ao centro <= centro
            int dist = abs(i - centro) + abs(j - centro);
            if (dist <= centro)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

// Sobrepõe a matriz de habilidade no tabuleiro na posição central (linhaOrigem, colunaOrigem)
void aplicaHabilidadeNoTabuleiro(int tab[TAB_SIZE][TAB_SIZE], int habilidade[HABILIDADE_SIZE][HABILIDADE_SIZE], int linhaOrigem, int colunaOrigem) {
    int centro = HABILIDADE_SIZE / 2;
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            if (habilidade[i][j] == 1) {
                int linTab = linhaOrigem - centro + i;
                int colTab = colunaOrigem - centro + j;
                // Verifica limites do tabuleiro
                if (linTab >= 0 && linTab < TAB_SIZE && colTab >= 0 && colTab < TAB_SIZE) {
                    // Marca área de efeito com valor 5, sem apagar navios (3)
                    if (tab[linTab][colTab] == 0) {
                        tab[linTab][colTab] = 5;
                    }
                }
            }
        }
    }
}

// Imprime o tabuleiro com símbolos
void imprimeTabuleiro(int tab[TAB_SIZE][TAB_SIZE]) {
    printf("Legenda: 0=agua  | 3=navio | 5=habilidade\n\n");
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            char c;
            switch (tab[i][j]) {
                case 0: c = '0'; break;   // água
                case 3: c = '3'; break;   // navio
                case 5: c = '5'; break;   // área de habilidade
                default: c = '?'; break;
            }
            printf("%c ", c);
        }
        printf("\n");
    }
}

// Implementações das funções de navio do código anterior

int podeColocarNavio(int tabuleiro[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, int orientacao) {
    int i, lin, col;

    for (i = 0; i < tamanho; i++) {
        switch (orientacao) {
            case 1: // Horizontal
                lin = linha;
                col = coluna + i;
                break;
            case 0: // Vertical
                lin = linha + i;
                col = coluna;
                break;
            case -1: // Diagonal descendente (linha+1, col+1)
                lin = linha + i;
                col = coluna + i;
                break;
            case -2: // Diagonal ascendente (linha-1, col+1)
                lin = linha - i;
                col = coluna + i;
                break;
            default:
                return 0; // Orientação inválida
        }

        // Verifica limites do tabuleiro
        if (lin < 0 || lin >= TAB_SIZE || col < 0 || col >= TAB_SIZE) {
            return 0;
        }

        // Verifica se já existe navio naquela posição
        if (tabuleiro[lin][col] != 0) {
            return 0;
        }
    }
    return 1;
}

void posicionaNavio(int tabuleiro[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, int orientacao) {
    for (int i = 0; i < tamanho; i++) {
        int lin, col;
        switch (orientacao) {
            case 1: // Horizontal
                lin = linha;
                col = coluna + i;
                break;
            case 0: // Vertical
                lin = linha + i;
                col = coluna;
                break;
            case -1: // Diagonal descendente
                lin = linha + i;
                col = coluna + i;
                break;
            case -2: // Diagonal ascendente
                lin = linha - i;
                col = coluna + i;
                break;
            default:
                return;
        }
        tabuleiro[lin][col] = 3; // Marca posição do navio
    }
}

int main() {
    int tabuleiro[TAB_SIZE][TAB_SIZE];
    inicializaTabuleiro(tabuleiro);

    // Posiciona navios (mesmo esquema do nível anterior)
    int n1_linha = 1, n1_coluna = 2, n1_orientacao = 1;   // Horizontal
    int n2_linha = 4, n2_coluna = 7, n2_orientacao = 0;   // Vertical
    int n3_linha = 6, n3_coluna = 1, n3_orientacao = -1;  // Diagonal descendente
    int n4_linha = 8, n4_coluna = 2, n4_orientacao = -2;  // Diagonal ascendente

    if (!podeColocarNavio(tabuleiro, n1_linha, n1_coluna, SHIP_SIZE, n1_orientacao) ||
        !podeColocarNavio(tabuleiro, n2_linha, n2_coluna, SHIP_SIZE, n2_orientacao) ||
        !podeColocarNavio(tabuleiro, n3_linha, n3_coluna, SHIP_SIZE, n3_orientacao) ||
        !podeColocarNavio(tabuleiro, n4_linha, n4_coluna, SHIP_SIZE, n4_orientacao)) {
        printf("Erro ao posicionar navios\n");
        return 1;
    }

    posicionaNavio(tabuleiro, n1_linha, n1_coluna, SHIP_SIZE, n1_orientacao);
    posicionaNavio(tabuleiro, n2_linha, n2_coluna, SHIP_SIZE, n2_orientacao);
    posicionaNavio(tabuleiro, n3_linha, n3_coluna, SHIP_SIZE, n3_orientacao);
    posicionaNavio(tabuleiro, n4_linha, n4_coluna, SHIP_SIZE, n4_orientacao);

    // Cria matrizes de habilidade
    int cone[HABILIDADE_SIZE][HABILIDADE_SIZE];
    int cruz[HABILIDADE_SIZE][HABILIDADE_SIZE];
    int octaedro[HABILIDADE_SIZE][HABILIDADE_SIZE];

    criaHabilidadeCone(cone);
    criaHabilidadeCruz(cruz);
    criaHabilidadeOctaedro(octaedro);

    // Define pontos de origem para as habilidades no tabuleiro
    int origemConeLinha = 2, origemConeColuna = 4;
    int origemCruzLinha = 7, origemCruzColuna = 7;
    int origemOctaedroLinha = 5, origemOctaedroColuna = 2;

    // Aplica as habilidades no tabuleiro
    aplicaHabilidadeNoTabuleiro(tabuleiro, cone, origemConeLinha, origemConeColuna);
    aplicaHabilidadeNoTabuleiro(tabuleiro, cruz, origemCruzLinha, origemCruzColuna);
    aplicaHabilidadeNoTabuleiro(tabuleiro, octaedro, origemOctaedroLinha, origemOctaedroColuna);

    // Imprime tabuleiro final
    imprimeTabuleiro(tabuleiro);
    printf("Pressione Enter para sair...");
    getchar();

    return 0;
}
