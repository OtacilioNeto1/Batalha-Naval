#include <stdio.h>

#define TAB_SIZE 10
#define SHIP_SIZE 3

// Função para inicializar o tabuleiro com água (0)
void inicializaTabuleiro(int tabuleiro[TAB_SIZE][TAB_SIZE]) {
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            tabuleiro[i][j] = 0; // 0 representa água
        }
    }
}

// Função para verificar se o navio pode ser colocado no tabuleiro
// Parâmetros:
// tabuleiro - matriz do tabuleiro
// linha, coluna - coordenadas iniciais
// tamanho - tamanho do navio
// horizontal - 1 se o navio é horizontal, 0 se vertical
// Retorna 1 se pode colocar, 0 se não pode
int podeColocarNavio(int tabuleiro[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, int horizontal) {
    if (horizontal) {
        // Verifica se navio cabe horizontalmente
        if (coluna + tamanho > TAB_SIZE) return 0;
        // Verifica se há sobreposição
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha][coluna + i] != 0) return 0;
        }
    } else {
        // Verifica se navio cabe verticalmente
        if (linha + tamanho > TAB_SIZE) return 0;
        // Verifica se há sobreposição
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha + i][coluna] != 0) return 0;
        }
    }
    return 1;
}

// Função para posicionar o navio no tabuleiro
void posicionaNavio(int tabuleiro[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, int horizontal) {
    if (horizontal) {
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linha][coluna + i] = 3; // 3 representa navio
        }
    } else {
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linha + i][coluna] = 3; // 3 representa navio
        }
    }
}

// Função para imprimir o tabuleiro no console
void imprimeTabuleiro(int tabuleiro[TAB_SIZE][TAB_SIZE]) {
    printf("Tabuleiro Batalha Naval (0=água, 3=navio):\n");
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            printf("%d ", tabuleiro[i][j]); // imprime valor com espaço
        }
        printf("\n"); // nova linha a cada linha do tabuleiro
    }
}

int main() {
    int tabuleiro[TAB_SIZE][TAB_SIZE];
    
    // Inicializa o tabuleiro com água
    inicializaTabuleiro(tabuleiro);
    
    // Definindo as coordenadas iniciais dos navios (linha, coluna)
    // Navio 1: horizontal, início em (2,3)
    int navio1Linha = 2;
    int navio1Coluna = 3;
    int navio1Horizontal = 1; // 1 = horizontal
    
    // Navio 2: vertical, início em (5,7)
    int navio2Linha = 5;
    int navio2Coluna = 7;
    int navio2Horizontal = 0; // 0 = vertical
    
    // Valida e posiciona navio 1
    if (podeColocarNavio(tabuleiro, navio1Linha, navio1Coluna, SHIP_SIZE, navio1Horizontal)) {
        posicionaNavio(tabuleiro, navio1Linha, navio1Coluna, SHIP_SIZE, navio1Horizontal);
    } else {
        printf("Não foi possível posicionar o navio 1 na posição (%d, %d)\n", navio1Linha, navio1Coluna);
        return 1; // sai do programa com erro
    }
    
    // Valida e posiciona navio 2
    if (podeColocarNavio(tabuleiro, navio2Linha, navio2Coluna, SHIP_SIZE, navio2Horizontal)) {
        posicionaNavio(tabuleiro, navio2Linha, navio2Coluna, SHIP_SIZE, navio2Horizontal);
    } else {
        printf("Não foi possível posicionar o navio 2 na posição (%d, %d)\n", navio2Linha, navio2Coluna);
        return 1; // sai do programa com erro
    }
    
    // Exibe o tabuleiro com os navios posicionados
    imprimeTabuleiro(tabuleiro);
    printf("Pressione Enter para sair...");
    getchar();
    
    return 0;
}
