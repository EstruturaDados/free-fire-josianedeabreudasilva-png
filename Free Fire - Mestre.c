#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define STR_SIZE 64

// --------------------------------------------------------
// STRUCT
// --------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // 1..10
} Componente;

// --------------------------------------------------------
// FUNÇÕES AUXILIARES
// --------------------------------------------------------

// Remove newline lido por fgets
void trim_newline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len-1] == '\n') s[len-1] = '\0';
}

// Lê string com fgets com proteção e trim
void ler_string(const char *prompt, char *buffer, int tamanho) {
    printf("%s", prompt);
    if (fgets(buffer, tamanho, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    trim_newline(buffer);
}

// Mostra vetor de componentes formatado
void mostrarComponentes(Componente comps[], int n) {
    printf("\n--- Componentes (total: %d) ---\n", n);
    printf("%-3s | %-25s | %-12s | %-9s\n", "ID", "NOME", "TIPO", "PRIORIDADE");
    printf("----+---------------------------+--------------+-----------\n");
    for (int i = 0; i < n; ++i) {
        printf("%-3d | %-25s | %-12s | %-9d\n",
               i, comps[i].nome, comps[i].tipo, comps[i].prioridade);
    }
    printf("-------------------------------\n");
}

// Troca dois componentes
void swapComp(Componente *a, Componente *b) {
    Componente tmp = *a;
    *a = *b;
    *b = tmp;
}

// --------------------------------------------------------
// ALGORITMOS DE ORDENAÇÃO (cada um retorna número de comparações)
// --------------------------------------------------------

// Bubble Sort por nome (string)
// Retorna número de comparações realizadas (long long)
long long bubbleSortNome(Componente comps[], int n) {
    long long comparacoes = 0;
    if (n <= 1) return comparacoes;

    for (int i = 0; i < n - 1; ++i) {
        int trocou = 0;
        for (int j = 0; j < n - 1 - i; ++j) {
            comparacoes++;
            if (strcmp(comps[j].nome, comps[j+1].nome) > 0) {
                swapComp(&comps[j], &comps[j+1]);
                trocou = 1;
            }
        }
        // otimização: se não trocou, já está ordenado
        if (!trocou) break;
    }
    return comparacoes;
}

// Insertion Sort por tipo (string)
long long insertionSortTipo(Componente comps[], int n) {
    long long comparacoes = 0;
    for (int i = 1; i < n; ++i) {
        Componente chave = comps[i];
        int j = i - 1;
        // comparamos tipos (strings)
        while (j >= 0) {
            comparacoes++;
            if (strcmp(comps[j].tipo, chave.tipo) > 0) {
                comps[j+1] = comps[j];
                j--;
            } else {
                break;
            }
        }
        comps[j+1] = chave;
    }
    return comparacoes;
}

// Selection Sort por prioridade (int) — ordena do maior para o menor (prioridade mais alta primeiro)
// Se preferir do menor para maior, basta inverter a comparação.
long long selectionSortPrioridade(Componente comps[], int n) {
    long long comparacoes = 0;
    for (int i = 0; i < n - 1; ++i) {
        int idxMelhor = i;
        for (int j = i + 1; j < n; ++j) {
            comparacoes++;
            // queremos prioridade maior primeiro:
            if (comps[j].prioridade > comps[idxMelhor].prioridade) {
                idxMelhor = j;
            }
        }
        if (idxMelhor != i) swapComp(&comps[i], &comps[idxMelhor]);
    }
    return comparacoes;
}

// --------------------------------------------------------
// BUSCA BINÁRIA (por nome) — só válida após ordenar por nome
// Retorna índice se encontrado, -1 se não.
// Também retorna número de comparações através do ponteiro compCount (long long*)
// --------------------------------------------------------
int buscaBinariaPorNome(Componente comps[], int n, const char *chave, long long *compCount) {
    int inicio = 0, fim = n - 1;
    *compCount = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*compCount)++;
        int cmp = strcmp(comps[meio].nome, chave);
        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// --------------------------------------------------------
// FUNÇÃO DE CADASTRO
// --------------------------------------------------------
int cadastrarComponentes(Componente comps[], int max) {
    int n = 0;
    char buffer[STR_SIZE];
    printf("\nCadastro de componentes (máx %d). Para parar, digite uma linha vazia no nome.\n", max);
    while (n < max) {
        ler_string("Nome do componente: ", buffer, STR_SIZE);
        if (strlen(buffer) == 0) break; // usuário deseja parar
        strncpy(comps[n].nome, buffer, sizeof(comps[n].nome)-1);
        comps[n].nome[sizeof(comps[n].nome)-1] = '\0';

        ler_string("Tipo (ex: controle, suporte, propulsao): ", buffer, STR_SIZE);
        strncpy(comps[n].tipo, buffer, sizeof(comps[n].tipo)-1);
        comps[n].tipo[sizeof(comps[n].tipo)-1] = '\0';

        // ler prioridade (int de 1 a 10)
        int p = 0;
        do {
            ler_string("Prioridade (1..10): ", buffer, STR_SIZE);
            p = atoi(buffer);
            if (p < 1 || p > 10) {
                printf("Prioridade inválida. Insira valor entre 1 e 10.\n");
            }
        } while (p < 1 || p > 10);
        comps[n].prioridade = p;

        n++;
        printf("Componente cadastrado com sucesso! (atual: %d)\n", n);
    }
    return n;
}

// --------------------------------------------------------
// MENU E INTEGRAÇÃO
// --------------------------------------------------------
void copiarArray(Componente dest[], Componente src[], int n) {
    for (int i = 0; i < n; ++i) dest[i] = src[i];
}

int main() {
    Componente compsOrig[MAX_COMPONENTES];
    Componente trabalho[MAX_COMPONENTES];
    int n = 0;

    printf("=== MÓDULO: MONTAGEM DA TORRE DE RESGATE ===\n");

    // cadastro inicial
    n = cadastrarComponentes(compsOrig, MAX_COMPONENTES);
    if (n == 0) {
        printf("Nenhum componente cadastrado. Encerrando.\n");
        return 0;
    }

    int opc;
    char chaveBusca[30];

    do {
        printf("\n----- MENU PRINCIPAL -----\n");
        printf("1 - Mostrar componentes cadastrados\n");
        printf("2 - Ordenar por NOME (Bubble Sort) e buscar chave (binária)\n");
        printf("3 - Ordenar por TIPO (Insertion Sort)\n");
        printf("4 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("5 - Re-cadastrar / sobrescrever lista\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d%*c", &opc) != 1) { // %*c consome newline
            // limpar stdin
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opc = -1;
        }

        if (opc == 1) {
            mostrarComponentes(compsOrig, n);
        }
        else if (opc == 2) {
            // bubble sort por nome
            copiarArray(trabalho, compsOrig, n);
            printf("\n--- Ordenando por NOME usando Bubble Sort ---\n");
            clock_t t0 = clock();
            long long comps = bubbleSortNome(trabalho, n);
            clock_t t1 = clock();
            double tempo = (double)(t1 - t0) / CLOCKS_PER_SEC;

            printf("Ordenação concluída. Comparações: %lld | Tempo: %.6f s\n", comps, tempo);
            mostrarComponentes(trabalho, n);

            // busca binária por nome (após ordenação)
            ler_string("Digite o NOME do componente-chave para busca binária: ", chaveBusca, sizeof(chaveBusca));
            long long compsBin = 0;
            clock_t b0 = clock();
            int idx = buscaBinariaPorNome(trabalho, n, chaveBusca, &compsBin);
            clock_t b1 = clock();
            double tempoBin = (double)(b1 - b0) / CLOCKS_PER_SEC;

            if (idx >= 0) {
                printf("\nComponente-CHAVE encontrado no índice %d.\n", idx);
                printf("Detalhes: Nome='%s', Tipo='%s', Prioridade=%d\n",
                       trabalho[idx].nome, trabalho[idx].tipo, trabalho[idx].prioridade);
            } else {
                printf("\nComponente-CHAVE NÃO encontrado.\n");
            }
            printf("Busca binária: comparações=%lld | tempo=%.6f s\n", compsBin, tempoBin);
        }
        else if (opc == 3) {
            // insertion sort por tipo
            copiarArray(trabalho, compsOrig, n);
            printf("\n--- Ordenando por TIPO usando Insertion Sort ---\n");
            clock_t t0 = clock();
            long long comps = insertionSortTipo(trabalho, n);
            clock_t t1 = clock();
            double tempo = (double)(t1 - t0) / CLOCKS_PER_SEC;
            printf("Ordenação concluída. Comparações: %lld | Tempo: %.6f s\n", comps, tempo);
            mostrarComponentes(trabalho, n);
            // informar que busca binária só aplica para ordenação por nome
            printf("Nota: busca binária não é aplicável automaticamente; ordenar por NOME primeiro para isso.\n");
        }
        else if (opc == 4) {
            // selection sort por prioridade
            copiarArray(trabalho, compsOrig, n);
            printf("\n--- Ordenando por PRIORIDADE usando Selection Sort ---\n");
            clock_t t0 = clock();
            long long comps = selectionSortPrioridade(trabalho, n);
            clock_t t1 = clock();
            double tempo = (double)(t1 - t0) / CLOCKS_PER_SEC;
            printf("Ordenação concluída. Comparações: %lld | Tempo: %.6f s\n", comps, tempo);
            mostrarComponentes(trabalho, n);
            printf("Ordem escolhida: prioridade maior -> menor (mais urgente primeiro).\n");
        }
        else if (opc == 5) {
            // recadastrar
            printf("\nSobrescrever lista de componentes.\n");
            n = cadastrarComponentes(compsOrig, MAX_COMPONENTES);
            if (n == 0) {
                printf("Nenhum componente cadastrado.\n");
            }
        }
        else if (opc == 0) {
            printf("Finalizando módulo. Boa sorte na fuga!\n");
        }
        else {
            printf("Opção inválida. Tente novamente.\n");
        }

    } while (opc != 0);

    return 0;
}