#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// -----------------------------------------------------------
// STRUCT PRINCIPAL DO INVENTÁRIO
// Armazena nome, tipo e quantidade de cada item
// -----------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// -----------------------------------------------------------
// FUNÇÃO: Inserir novo item no inventário
// -----------------------------------------------------------
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\n⚠️ A mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("\nDigite o nome do item: ");
    scanf("%s", novo.nome);

    printf("Digite o tipo (arma, municao, cura, ferramenta): ");
    scanf("%s", novo.tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*total] = novo;
    (*total)++;

    printf("\n✅ Item adicionado com sucesso!\n");
}

// -----------------------------------------------------------
// FUNÇÃO: Remover item pelo nome
// -----------------------------------------------------------
void removerItem(Item mochila[], int *total) {
    char nomeBusca[30];
    int i, j;
    int encontrado = 0;

    if (*total == 0) {
        printf("\n A mochila está vazia! Nada para remover.\n");
        return;
    }

    printf("\nDigite o nome do item que deseja remover: ");
    scanf("%s", nomeBusca);

    for (i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;

            for (j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            (*total)--;

            printf("\n Item removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\n Item não encontrado na mochila!\n");
    }
}

// -----------------------------------------------------------
// FUNÇÃO: Listar todos os itens
// -----------------------------------------------------------
void listarItens(Item mochila[], int total) {
    printf("\n----------- ITENS NA MOCHILA -----------\n");

    if (total == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("\nItem %d:\n", i + 1);
        printf(" Nome: %s\n", mochila[i].nome);
        printf(" Tipo: %s\n", mochila[i].tipo);
        printf(" Quantidade: %d\n", mochila[i].quantidade);
    }
    printf("-----------------------------------------\n");
}

// -----------------------------------------------------------
// FUNÇÃO: Buscar item (busca sequencial)
// -----------------------------------------------------------
void buscarItem(Item mochila[], int total) {
    char nomeBusca[30];
    int encontrado = 0;

    if (total == 0) {
        printf("\n A mochila está vazia! Nada para buscar.\n");
        return;
    }

    printf("\nDigite o nome do item para buscar: ");
    scanf("%s", nomeBusca);

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            printf("\n Item encontrado!\n");
            printf(" Nome: %s\n", mochila[i].nome);
            printf(" Tipo: %s\n", mochila[i].tipo);
            printf(" Quantidade: %d\n", mochila[i].quantidade);
            break;
        }
    }

    if (!encontrado) {
        printf("\n Item não encontrado!\n");
    }
}

// -----------------------------------------------------------
// FUNÇÃO PRINCIPAL (MENU DO JOGADOR)
// -----------------------------------------------------------
int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n============================================\n");
        printf("        SISTEMA DE INVENTÁRIO - LOOT\n");
        printf("============================================\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha sua opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &total);
                listarItens(mochila, total);
                break;

            case 2:
                removerItem(mochila, &total);
                listarItens(mochila, total);
                break;

            case 3:
                listarItens(mochila, total);
                break;

            case 4:
                buscarItem(mochila, total);
                break;

            case 0:
                printf("\nSaindo do sistema... Até mais, jogador!\n");
                break;

            default:
                printf("\n⚠️ Opção inválida! Tente novamente.\n");
        }

        } while (opcao != 0);
    
        return 0;
    }