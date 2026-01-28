#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> // Necessária para medir o tempo (clock())

// --- CONSTANTES ---
#define MAX_COMPONENTE 20 // Requisito: até 20 componentes
#define MAX_STRING 50

// --- ESTRUTURAS ---
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Estrutura para organizar os componentes no sistema
typedef struct {
    Componente lista[MAX_COMPONENTE];
    int total;
} SistemaTorre;

// --- PROTÓTIPOS ---
void inserirComponente(SistemaTorre *s);
void mostrarComponentes(Componente vetor[], int total);
void bubbleSortNome(Componente vetor[], int total);
void insertionSortTipo(Componente vetor[], int total);
void selectionSortPrioridade(Componente vetor[], int total);
void buscaBinariaPorNome(Componente vetor[], int total, char busca[]);

// --- MAIN ---
int main() {
    SistemaTorre torre;
    torre.total = 0;
    int opcao;
    char entrada[10];
    char nomeBusca[30];

    do {
        printf("\n========== SISTEMA DE FUGA - TORRE ==========\n");
        printf("Componentes Cadastrados: %d/%d\n", torre.total, MAX_COMPONENTE);
        printf("1. Cadastrar Componente\n");
        printf("2. Ordenar por Nome (Bubble Sort)\n");
        printf("3. Ordenar por Tipo (Insertion Sort)\n");
        printf("4. Ordenar por Prioridade (Selection Sort)\n");
        printf("5. Buscar Componente-Chave (Busca Binaria)\n");
        printf("6. Listar Componentes\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        
        fgets(entrada, 10, stdin);
        opcao = atoi(entrada);

        switch(opcao) {
            case 1: inserirComponente(&torre); break;
            case 2: bubbleSortNome(torre.lista, torre.total); break;
            case 3: insertionSortTipo(torre.lista, torre.total); break;
            case 4: selectionSortPrioridade(torre.lista, torre.total); break;
            case 5: 
                printf("Digite o nome do componente-chave: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                buscaBinariaPorNome(torre.lista, torre.total, nomeBusca);
                break;
            case 6: mostrarComponentes(torre.lista, torre.total); break;
            case 0: printf("Iniciando sequencia de escape...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

void inserirComponente(SistemaTorre *s) {
    if (s->total >= MAX_COMPONENTE) {
        printf("[ERRO] Limite de componentes atingido!\n");
        return;
    }
    Componente *c = &s->lista[s->total];

    printf("Nome do componente: ");
    fgets(c->nome, 30, stdin);
    c->nome[strcspn(c->nome, "\n")] = 0;

    printf("Tipo (Controle, Suporte, Propulsao): ");
    fgets(c->tipo, 20, stdin);
    c->tipo[strcspn(c->tipo, "\n")] = 0;

    printf("Prioridade (1 a 10): ");
    scanf("%d", &c->prioridade);
    getchar(); // Limpa o buffer

    s->total++;
    printf("Componente adicionado ao plano de fuga!\n");
}

void mostrarComponentes(Componente vetor[], int total) {
    if (total == 0) {
        printf("\nNenhum componente cadastrado.\n");
        return;
    }
    printf("\n%-20s | %-15s | %-10s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("%-20s | %-15s | %-10d\n", vetor[i].nome, vetor[i].tipo, vetor[i].prioridade);
    }
}

// 1. BUBBLE SORT - Critério: NOME (String)
void bubbleSortNome(Componente vetor[], int total) {
    clock_t inicio = clock(); // Inicia o cronômetro
    int comparacoes = 0;
    Componente temp;

    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - 1 - i; j++) {
            comparacoes++;
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
    clock_t fim = clock(); // Para o cronômetro
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n[BUBBLE SORT] Ordenado por NOME.");
    printf("\nComparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
}

// 2. INSERTION SORT - Critério: TIPO (String)
void insertionSortTipo(Componente vetor[], int total) {
    clock_t inicio = clock();
    int comparacoes = 0;
    
    for (int i = 1; i < total; i++) {
        Componente chave = vetor[i];
        int j = i - 1;

        while (j >= 0 && strcmp(vetor[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n[INSERTION SORT] Ordenado por TIPO.");
    printf("\nComparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
}

// 3. SELECTION SORT - Critério: PRIORIDADE (Inteiro)
void selectionSortPrioridade(Componente vetor[], int total) {
    clock_t inicio = clock();
    int comparacoes = 0;

    for (int i = 0; i < total - 1; i++) {
        int min = i;
        for (int j = i + 1; j < total; j++) {
            comparacoes++;
            if (vetor[j].prioridade < vetor[min].prioridade) {
                min = j;
            }
        }
        Componente temp = vetor[i];
        vetor[i] = vetor[min];
        vetor[min] = temp;
    }
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n[SELECTION SORT] Ordenado por PRIORIDADE.");
    printf("\nComparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
}

// 4. BUSCA BINÁRIA - Critério: NOME
void buscaBinariaPorNome(Componente vetor[], int total, char busca[]) {
    int comparacoes = 0;
    int inicio = 0, fim = total - 1;

    while (inicio <= fim) {
        comparacoes++;
        int meio = (inicio + fim) / 2;
        int res = strcmp(vetor[meio].nome, busca);

        if (res == 0) {
            printf("\n[SUCESSO] Componente-chave '%s' localizado!", busca);
            printf("\nTipo: %s | Prioridade: %d", vetor[meio].tipo, vetor[meio].prioridade);
            printf("\nComparacoes na Busca Binaria: %d\n", comparacoes);
            return;
        } else if (res < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("\n[AVISO] Componente '%s' nao encontrado. Verifique se o vetor esta ordenado por NOME.\n", busca);
}