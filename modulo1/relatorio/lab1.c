#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MODO 0 // Trocar para o modo desejado (opções abaixo).

#define ALEATORIO 0
#define  ORDENADO 1
#define INVERTIDO 2

void testar(int modo, int tamanho, FILE *bubble, FILE *insertion, FILE *merge);
void gerar_vetores(int modo, int tamanho, int **ptr1, int **ptr2, int **ptr3);
void imprimir_vetor(int* vetor, int tamanho_vetor);

void bubbleSort(int *vetor, int tamanho);
void insertionSort(int *vetor, int tamanho);
void intercala(int *vetor, int inicio, int centro, int fim);
void mergeSort(int *vetor, int inicio, int fim);


int main(int argc, char **argv)
{
    // Criar arquivos.
    FILE *bubble_fp    = fopen("bubble.csv", "w");
    FILE *insertion_fp = fopen("insertion.csv", "w");
    FILE *merge_fp     = fopen("merge.csv", "w");

    // Escrever cabeçalhos.
    fprintf(bubble_fp,    "vector_type,vector_size,iteration,execution_time\n");
    fprintf(insertion_fp, "vector_type,vector_size,iteration,execution_time\n");
    fprintf(merge_fp,     "vector_type,vector_size,iteration,execution_time\n");

    // Executar testes.
    testar(MODO,    25, bubble_fp, insertion_fp, merge_fp);
    testar(MODO,   100, bubble_fp, insertion_fp, merge_fp);
    testar(MODO,   500, bubble_fp, insertion_fp, merge_fp);
    testar(MODO,  1000, bubble_fp, insertion_fp, merge_fp);
    testar(MODO,  2500, bubble_fp, insertion_fp, merge_fp);
    testar(MODO,  5000, bubble_fp, insertion_fp, merge_fp);
    testar(MODO,  7500, bubble_fp, insertion_fp, merge_fp);
    testar(MODO, 10000, bubble_fp, insertion_fp, merge_fp);
    testar(MODO, 15000, bubble_fp, insertion_fp, merge_fp);
    testar(MODO, 20000, bubble_fp, insertion_fp, merge_fp);
    testar(MODO, 25000, bubble_fp, insertion_fp, merge_fp);
    testar(MODO, 30000, bubble_fp, insertion_fp, merge_fp);
    testar(MODO, 35000, bubble_fp, insertion_fp, merge_fp);
    testar(MODO, 40000, bubble_fp, insertion_fp, merge_fp);
    testar(MODO, 45000, bubble_fp, insertion_fp, merge_fp);
    testar(MODO, 50000, bubble_fp, insertion_fp, merge_fp);

    // Teste de pior caso.
    // testar(0, 1000, bubble_fp, insertion_fp, merge_fp);
    // testar(1, 1000, bubble_fp, insertion_fp, merge_fp);
    // testar(2, 1000, bubble_fp, insertion_fp, merge_fp);
    
    // Fechar arquivos.
    fclose(bubble_fp);
    fclose(insertion_fp);
    fclose(merge_fp);

    return 0;
}


void testar(int modo, int tamanho, FILE *bubble, FILE *insertion, FILE *merge)
{
    clock_t inicial, final;

    for (int i = 0; i < 10; i++)
    {
        int *vetor_bubble = NULL;
        int *vetor_insertion = NULL;
        int *vetor_merge = NULL;

        gerar_vetores(modo, tamanho, &vetor_bubble, &vetor_insertion, &vetor_merge);

        // Bubble:
        inicial = clock();
        bubbleSort(vetor_bubble, tamanho);
        final = clock();
        fprintf(bubble, "%d,%d,%d,%lf\n", modo, tamanho, i + 1, (final - inicial) / (double)CLOCKS_PER_SEC);
        free(vetor_bubble);

        // Insertion:
        inicial = clock();
        insertionSort(vetor_insertion, tamanho);
        final = clock();
        fprintf(insertion, "%d,%d,%d,%lf\n", modo, tamanho, i + 1, (final - inicial) / (double)CLOCKS_PER_SEC);
        free(vetor_insertion);

        // Merge:
        inicial = clock();
        mergeSort(vetor_merge, 0, tamanho - 1);
        final = clock();
        fprintf(merge, "%d,%d,%d,%lf\n", modo, tamanho, i + 1, (final - inicial) / (double)CLOCKS_PER_SEC);
        free(vetor_merge);
    }
}

void gerar_vetores(int modo, int tamanho, int **ptr1, int **ptr2, int **ptr3)
{
    int *vetor1 = (int *) malloc(tamanho * sizeof(int));
    int *vetor2 = (int *) malloc(tamanho * sizeof(int));
    int *vetor3 = (int *) malloc(tamanho * sizeof(int));

    srand(time(NULL));

    for (int i = 0; i < tamanho; i++)
    {
        if (modo == ALEATORIO)
            vetor1[i] = rand() % (2 * tamanho);
        else if (modo == ORDENADO)
            vetor1[i] = i;
        else if (modo == INVERTIDO)
            vetor1[i] = tamanho - i;

        vetor2[i] = vetor1[i];
        vetor3[i] = vetor1[i];
    }

    *ptr1 = vetor1;
    *ptr2 = vetor2;
    *ptr3 = vetor3;
}

void imprimir_vetor(int* vetor, int tamanho_vetor)
{
    for (int i = 0; i < tamanho_vetor; i++)
        printf("%i ", vetor[i]);
    printf("\n");
}

/******************************************************************************
 *      ALGORITMOS DE ORDENAÇÃO: Bubble Sort, Insertion Sort, Merge Sort      *
 ******************************************************************************/

void bubbleSort(int *vetor, int tamanho)
{
    int i, j;
    for (i = 0; i < tamanho - 1; i++)
    {
        for (j = 0; j < tamanho - 1 - i; j++)
        {
            if (vetor[j] > vetor[j + 1])
            {
                int aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

void insertionSort(int *vetor, int tamanho)
{
    int j;
    for (j = 1; j < tamanho; j++)
    {
        int chave = vetor[j];
        int i = j - 1;
        while (i >= 0 && vetor[i] > chave)
        {
            vetor[i + 1] = vetor[i];
            i--;
        }
        vetor[i + 1] = chave;
    }
}

void intercala(int *vetor, int inicio, int centro, int fim)
{
    int *vetorAux = (int *)malloc(sizeof(int) * (fim - inicio) + 1);

    int i = inicio;
    int j = centro + 1;
    int k = 0;

    while (i <= centro && j <= fim)
    {
        if (vetor[i] <= vetor[j])
        {
            vetorAux[k] = vetor[i];
            i++;
        }
        else
        {
            vetorAux[k] = vetor[j];
            j++;
        }
        k++;
    }

    while (i <= centro)
    {
        vetorAux[k] = vetor[i];
        i++;
        k++;
    }

    while (j <= fim)
    {
        vetorAux[k] = vetor[j];
        j++;
        k++;
    }

    for (i = inicio, k = 0; i <= fim; i++, k++)
        vetor[i] = vetorAux[k];

    free(vetorAux);
}

void mergeSort(int *vetor, int inicio, int fim)
{
    if (fim <= inicio)
        return;

    int centro = (int)((inicio + fim) / 2.0);
    mergeSort(vetor, inicio, centro);
    mergeSort(vetor, centro + 1, fim);

    intercala(vetor, inicio, centro, fim);
}