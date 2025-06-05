#include <stdio.h>

#define TAB_SIZE 10
#define SHIP_SIZE 3

// Inicializa o tabuleiro com água (0)
void inicializaTabuleiro(int tabuleiro[TAB_SIZE][TAB_SIZE]) {
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Verifica se navio pode ser colocado horizontal, vertical ou diagonal
// horizontal: 1 = horizontal, 0 = vertical, -1 = diagonal descendente (linha+1,col+1), -2 = diagonal ascendente (linha-1,col+1)
// Retorna 1 se pode, 0 se não pode
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

// Posiciona o navio no tabuleiro
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

// Imprime o tabuleiro no console
void imprimeTabuleiro(int tabuleiro[TAB_SIZE][TAB_SIZE]) {
    printf("Tabuleiro Batalha Naval (0=agua, 3=navio):\n");
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAB_SIZE][TAB_SIZE];
    inicializaTabuleiro(tabuleiro);

    // Definição dos navios:
    // Orientações: 1 = horizontal, 0 = vertical, -1 = diagonal descendente, -2 = diagonal ascendente
    // Navio 1: horizontal, início em (1,2)
    int n1_linha = 1, n1_coluna = 2, n1_orientacao = 1;

    // Navio 2: vertical, início em (4,7)
    int n2_linha = 4, n2_coluna = 7, n2_orientacao = 0;

    // Navio 3: diagonal descendente, início em (6,1)
    int n3_linha = 6, n3_coluna = 1, n3_orientacao = -1;

    // Navio 4: diagonal ascendente, início em (8,2)
    int n4_linha = 8, n4_coluna = 2, n4_orientacao = -2;

    // Valida e posiciona navio 1
    if (podeColocarNavio(tabuleiro, n1_linha, n1_coluna, SHIP_SIZE, n1_orientacao)) {
        posicionaNavio(tabuleiro, n1_linha, n1_coluna, SHIP_SIZE, n1_orientacao);
    } else {
        printf("Não foi possível posicionar o navio 1.\n");
        return 1;
    }

    // Valida e posiciona navio 2
    if (podeColocarNavio(tabuleiro, n2_linha, n2_coluna, SHIP_SIZE, n2_orientacao)) {
        posicionaNavio(tabuleiro, n2_linha, n2_coluna, SHIP_SIZE, n2_orientacao);
    } else {
        printf("Não foi possível posicionar o navio 2.\n");
        return 1;
    }

    // Valida e posiciona navio 3 (diagonal descendente)
    if (podeColocarNavio(tabuleiro, n3_linha, n3_coluna, SHIP_SIZE, n3_orientacao)) {
        posicionaNavio(tabuleiro, n3_linha, n3_coluna, SHIP_SIZE, n3_orientacao);
    } else {
        printf("Não foi possível posicionar o navio 3.\n");
        return 1;
    }

    // Valida e posiciona navio 4 (diagonal ascendente)
    if (podeColocarNavio(tabuleiro, n4_linha, n4_coluna, SHIP_SIZE, n4_orientacao)) {
        posicionaNavio(tabuleiro, n4_linha, n4_coluna, SHIP_SIZE, n4_orientacao);
    } else {
        printf("Não foi possível posicionar o navio 4.\n");
        return 1;
    }

    // Exibe o tabuleiro com navios posicionados
    imprimeTabuleiro(tabuleiro);
    printf("Pressione Enter para sair...");
    getchar();

    return 0;
}
