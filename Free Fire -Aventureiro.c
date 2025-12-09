#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------------
// STRUCTS PRINCIPAIS
// ---------------------------------------------------------

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ---------------------------------------------------------
// VARIÁVEIS GLOBAIS
// ---------------------------------------------------------

#define MAX_ITENS 100
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;

No* mochilaLista = NULL;

int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ---------------------------------------------------------
// FUNÇÕES PARA O VETOR
// ---------------------------------------------------------

void inserirItemVetor(Item novo) {
    if (totalItensVetor >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }
    mochilaVetor[totalItensVetor++] = novo;
    printf("\nItem inserido no vetor!\n");
}

void removerItemVetor(char nome[]) {
    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            totalItensVetor--;
            printf("\nItem removido do vetor!\n");
            return;
        }
    }
    printf("\nItem não encontrado!\n");
}

void listarVetor() {
    printf("\n--- Itens do vetor ---\n");
    for (int i = 0; i < totalItensVetor; i++) {
        printf("Nome: %s | Tipo: %s | Qtde: %d\n",
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }
}

int buscarSequencialVetor(char nome[]) {
    comparacoesSequencial = 0;
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

void ordenarVetor() {
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - 1 - i; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("\nVetor ordenado por nome!\n");
}

int buscarBinariaVetor(char nome[]) {
    comparacoesBinaria = 0;
    int inicio = 0, fim = totalItensVetor - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(mochilaVetor[meio].nome, nome);

        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// ---------------------------------------------------------
// FUNÇÕES PARA A LISTA ENCADEADA
// ---------------------------------------------------------

void inserirItemLista(Item novo) {
    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->dados = novo;
    novoNo->proximo = mochilaLista;
    mochilaLista = novoNo;
    printf("\nItem inserido na lista encadeada!\n");
}

void removerItemLista(char nome[]) {
    No* atual = mochilaLista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                mochilaLista = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("\nItem removido da lista!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("\nItem não encontrado!\n");
}

void listarLista() {
    printf("\n--- Itens da lista encadeada ---\n");

    No* atual = mochilaLista;
    while (atual != NULL) {
        printf("Nome: %s | Tipo: %s | Qtde: %d\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
    }
}

int buscarSequencialLista(char nome[]) {
    comparacoesSequencial = 0;
    No* atual = mochilaLista;

    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            return 1; // encontrado
        }
        atual = atual->proximo;
    }
    return -1;
}

// ---------------------------------------------------------
// FUNÇÃO PARA LER ITEM
// ---------------------------------------------------------

Item lerItem() {
    Item novo;
    printf("Nome do item: ");
    scanf(" %[^\n]", novo.nome);

    printf("Tipo do item: ");
    scanf(" %[^\n]", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    return novo;
}

// ---------------------------------------------------------
// MENUS
// ---------------------------------------------------------

void menuVetor() {
    int opc;
    char nome[30];

    do {
        printf("\n==== MENU VETOR ====\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar sequencial\n");
        printf("5 - Ordenar vetor\n");
        printf("6 - Buscar binária\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                inserirItemVetor(lerItem());
                break;

            case 2:
                printf("Nome a remover: ");
                scanf(" %[^\n]", nome);
                removerItemVetor(nome);
                break;

            case 3:
                listarVetor();
                break;

            case 4:
                printf("Nome para busca: ");
                scanf(" %[^\n]", nome);
                int pos;
                pos = buscarSequencialVetor(nome);
                printf(pos >= 0 ? "\nEncontrado!\n" : "\nNão encontrado!\n");
                printf("Comparações (sequencial): %d\n", comparacoesSequencial);
                break;

            case 5:
                ordenarVetor();
                break;

            case 6:
                printf("Nome para busca binária: ");
                scanf(" %[^\n]", nome);
                pos = buscarBinariaVetor(nome);
                printf(pos >= 0 ? "\nEncontrado!\n" : "\nNão encontrado!\n");
                printf("Comparações (binária): %d\n", comparacoesBinaria);
                break;
        }

    } while (opc != 0);
}

void menuLista() {
    int opc;
    char nome[30];

    do {
        printf("\n==== MENU LISTA ====\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar sequencial\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                inserirItemLista(lerItem());
                break;

            case 2:
                printf("Nome a remover: ");
                scanf(" %[^\n]", nome);
                removerItemLista(nome);
                break;

            case 3:
                listarLista();
                break;

            case 4:
                printf("Nome para busca: ");
                scanf(" %[^\n]", nome);
                int encontrado;
                encontrado = buscarSequencialLista(nome);
                printf(encontrado > 0 ? "\nEncontrado!\n" : "\nNão encontrado!\n");
                printf("Comparações (sequencial): %d\n", comparacoesSequencial);
                break;
        }

    } while (opc != 0);
}

// ---------------------------------------------------------
// MAIN
// ---------------------------------------------------------

int main() {
    int opc;

    do {
        printf("\n==== SISTEMA DE MOCHILA ====\n");
        printf("1 - Usar Vetor\n");
        printf("2 - Usar Lista Encadeada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuLista();
                break;
        }

    } while (opc != 0);

    return 0;
}