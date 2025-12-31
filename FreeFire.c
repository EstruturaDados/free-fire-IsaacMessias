#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// --- CONSTANTES ---
#define MAX_ITEM 10
#define MAX_STRING 50

// --- ESTRUTURAS ---
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Estrutura para a Mochila que contém o vetor de itens
typedef struct {
    Item itens[MAX_ITEM];
    int total; // Controle de quantos itens existem atualmente
} Mochila;


// --- PROTÓTIPOS ---
void inserirItem(Mochila *m);
void removerItem(Mochila *m);
void listarItens(Mochila *m);
void buscarItem(Mochila *m);

// --- MAIN ---
int main() {
    Mochila minhaMochila;
    minhaMochila.total = 0; // Inicializa a lista vazia
    int opcao;
    char entrada[10];

    do {
        printf("==============================\n");
        printf("-- MOCHILA DE SOBREVIVENCIA --\n");
        printf("==============================\n");
        printf("Itens na mochila: %d/10\n", minhaMochila.total);

        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        
        fgets(entrada, 10, stdin);
        opcao = atoi(entrada);

        switch(opcao) {
            case 1: inserirItem(&minhaMochila); break;
            case 2: removerItem(&minhaMochila); break;
            case 3: listarItens(&minhaMochila); break;
            case 4: buscarItem(&minhaMochila); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

void inserirItem(Mochila *m) {
    if (m->total >= MAX_ITEM) {
        printf("\n[ERRO] Mochila cheia! Remova algo antes.\n");
        return;
    }

    printf("\n--- Cadastro de Item ---\n");
    printf("Nome: ");
    fgets(m->itens[m->total].nome, 30, stdin);
    m->itens[m->total].nome[strcspn(m->itens[m->total].nome, "\n")] = 0; // Remove o \n

    printf("Tipo (arma, municao, cura): ");
    fgets(m->itens[m->total].tipo, 20, stdin);
    m->itens[m->total].tipo[strcspn(m->itens[m->total].tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &m->itens[m->total].quantidade);
    getchar(); // Limpa o buffer do teclado

    m->total++;
    printf("\nItem cadastrado com sucesso!\n");
    listarItens(m); // Requisito: listar após cada operação
}

void listarItens(Mochila *m) {
    if (m->total == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }
    printf("\n--- LISTAGEM DE ITENS (%d/%d) ---\n", m->total, MAX_ITEM);
    for (int i = 0; i < m->total; i++) {
        printf("%d. %s | Tipo: %s | Qtd: %d\n", 
               i + 1, m->itens[i].nome, m->itens[i].tipo, m->itens[i].quantidade);
    }
}

void buscarItem(Mochila *m) {
    char busca[30];
    printf("\nDigite o nome do item para buscar: ");
    fgets(busca, 30, stdin);
    busca[strcspn(busca, "\n")] = 0;

    // Busca Sequencial (Requisito Funcional)
    for (int i = 0; i < m->total; i++) {
        if (strcmp(m->itens[i].nome, busca) == 0) {
            printf("\nItem localizado: %s | Tipo: %s | Qtd: %d\n", 
                   m->itens[i].nome, m->itens[i].tipo, m->itens[i].quantidade);
            return;
        }
    }
    printf("\nItem '%s' nao encontrado.\n", busca);
}

void removerItem(Mochila *m) {
    char busca[30];
    printf("\nDigite o nome do item para remover: ");
    fgets(busca, 30, stdin);
    busca[strcspn(busca, "\n")] = 0;

    for (int i = 0; i < m->total; i++) {
        if (strcmp(m->itens[i].nome, busca) == 0) {
            // "Puxa" os itens da frente para trás para manter o vetor contíguo
            for (int j = i; j < m->total - 1; j++) {
                m->itens[j] = m->itens[j + 1];
            }
            m->total--;
            printf("\nItem '%s' removido!\n", busca);
            listarItens(m);
            return;
        }
    }
    printf("\nItem nao encontrado.\n");
}
// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da  maisalta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
