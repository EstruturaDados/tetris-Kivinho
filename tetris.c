#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5   // Tamanho fixo da fila circular

// -------------------------------------------------------------
// Struct que representa uma peça do Tetris
// nome = tipo da peça (I, O, T, L, S, Z, J)
// id   = identificador numérico único
// -------------------------------------------------------------
typedef struct {
    char nome;
    int id;
} Peca;


// -------------------------------------------------------------
// Variáveis globais da fila circular:
// fila[]  -> armazena as peças
// inicio  -> índice do primeiro elemento (dequeue)
// fim     -> índice do último elemento (enqueue)
// count   -> quantidade atual de peças na fila (sempre 0 a 5)
// -------------------------------------------------------------
Peca fila[TAM_FILA];
int inicio = 0;
int fim = -1;
int count = 0;
int idGlobal = 1;


// -------------------------------------------------------------
// Função gerarPeca()
// Gera automaticamente uma peça com nome aleatório de Tetris
// Atribui também um ID único incrementado globalmente
// -------------------------------------------------------------
Peca gerarPeca() {
    char tipos[7] = {'I','O','T','L','J','S','Z'};
    Peca p;
    p.nome = tipos[rand() % 7];
    p.id = idGlobal++;
    return p;
}


// -------------------------------------------------------------
// Função enqueue()
// Insere uma nova peça no final da fila circular
// Respeita reaproveitamento do espaço mod TAM_FILA
// -------------------------------------------------------------
void enqueue(Peca p) {
    if (count == TAM_FILA) {
        printf("\n[FILA CHEIA] Não é possível inserir.\n");
        return;
    }

    fim = (fim + 1) % TAM_FILA;
    fila[fim] = p;
    count++;
    printf("\nPeça inserida: %c (%d)\n", p.nome, p.id);
}


// -------------------------------------------------------------
// Função dequeue()
// Remove a peça da frente da fila circular
// Avança o índice "inicio" de forma circular
// -------------------------------------------------------------
void dequeue() {
    if (count == 0) {
        printf("\n[FILA VAZIA] Nenhuma peça para jogar.\n");
        return;
    }

    Peca removida = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    count--;

    printf("\nPeça jogada/removida: %c (%d)\n", removida.nome, removida.id);
}


// -------------------------------------------------------------
// Função visualizar()
// Mostra o estado atual da fila circular em ordem lógica
// -------------------------------------------------------------
void visualizar() {
    printf("\n===== FILA ATUAL =====\n");

    if (count == 0) {
        printf("(vazia)\n");
        return;
    }

    int idx = inicio;
    for (int i = 0; i < count; i++) {
        printf("[%d] %c (%d)\n", i, fila[idx].nome, fila[idx].id);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("======================\n");
}


// -------------------------------------------------------------
// Função inicializarFila()
// Preenche a fila com 5 peças geradas automaticamente
// -------------------------------------------------------------
void inicializarFila() {
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(gerarPeca());
    }
}


// -------------------------------------------------------------
// Função principal – loop do menu
// -------------------------------------------------------------
int main() {
    srand(time(NULL));  // Seed para nomes aleatórios

    printf("Inicializando a fila com 5 peças...\n");
    inicializarFila();
    visualizar();

    int opcao;

    do {
        printf("\n=== MENU TETRIS STACK ===\n");
        printf("1 - Jogar/Remover peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("3 - Visualizar fila\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                dequeue();
                visualizar();
                break;
            case 2:
                enqueue(gerarPeca());
                visualizar();
                break;
            case 3:
                visualizar();
                break;
            case 0:
                printf("\nEncerrando...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

/*#include <stdio.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

int main() {

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.



    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


    return 0;
}

