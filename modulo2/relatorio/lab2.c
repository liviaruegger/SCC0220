#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MODO 0 // Trocar para o modo desejado (opções abaixo).

#define ALEATORIO 0
#define  ORDENADO 1
#define INVERTIDO 2

void testar(int modo, int tamanho, FILE *bubble, FILE *insertion, FILE *merge, FILE *quick, FILE *heap);
void gerar_vetores(int modo, int tamanho, int **ptr1, int **ptr2, int **ptr3, int **ptr4, int **ptr5);
void imprimir_vetor(int* vetor, int tamanho_vetor);

void bubbleSort(int *vetor, int tamanho);
void insertionSort(int *vetor, int tamanho);
void intercala(int *vetor, int inicio, int centro, int fim);
void mergeSort(int *vetor, int inicio, int fim);

void quicksort(int* v, int ini, int fim);
void max_heapify(int *v, int p, int N);
void build_maxheap(int *v, int N);
void heapsort(int *v, int N);


int main()
{
    // Criar arquivos.
    FILE *bubble_fp    = fopen("bubble.csv", "w");
    FILE *insertion_fp = fopen("insertion.csv", "w");
    FILE *merge_fp     = fopen("merge.csv", "w");
    FILE *quick_fp     = fopen("quick.csv", "w");
    FILE *heap_fp      = fopen("heap.csv", "w");

    // Escrever cabeçalhos.
    fprintf(bubble_fp,    "vector_type,vector_size,iteration,execution_time\n");
    fprintf(insertion_fp, "vector_type,vector_size,iteration,execution_time\n");
    fprintf(merge_fp,     "vector_type,vector_size,iteration,execution_time\n");
    fprintf(quick_fp,     "vector_type,vector_size,iteration,execution_time\n");
    fprintf(heap_fp,      "vector_type,vector_size,iteration,execution_time\n");

    /* // TESTE 1 (quicksort, heapsort)
    testar(MODO,     25, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,    100, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,    500, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,   1000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,   2500, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,   5000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,   7500, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  10000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  15000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  20000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  25000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  30000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  35000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  40000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  45000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  50000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  55000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  60000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  65000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  70000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  75000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  80000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  85000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  90000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  95000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO, 100000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp); */

    // TESTE 2 (comparação com módulo 1)
    testar(MODO,    25, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,   100, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,   500, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  1000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  2500, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  5000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO,  7500, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO, 10000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO, 15000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO, 20000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO, 25000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO, 30000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO, 35000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO, 40000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO, 45000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(MODO, 50000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);

    /* // TESTE 3 (pior caso)
    testar(0, 1000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(1, 1000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp);
    testar(2, 1000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp); */
    
    // Fechar arquivos.
    fclose(bubble_fp);
    fclose(insertion_fp);
    fclose(merge_fp);
    fclose(quick_fp);
    fclose(heap_fp);

    return 0;
}


void testar(int modo, int tamanho, FILE *bubble, FILE *insertion, FILE *merge, FILE *quick, FILE *heap)
{
    clock_t inicial, final;

    for (int i = 0; i < 10; i++)
    {
        int *vetor_bubble    = NULL;
        int *vetor_insertion = NULL;
        int *vetor_merge     = NULL;
        int *vetor_quick     = NULL;
        int *vetor_heap      = NULL;

        gerar_vetores(modo, tamanho, &vetor_bubble, &vetor_insertion, &vetor_merge, &vetor_quick, &vetor_heap);

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

        // Quick:
        inicial = clock();
        quicksort(vetor_quick, 0, tamanho - 1);
        final = clock();
        fprintf(quick, "%d,%d,%d,%lf\n", modo, tamanho, i + 1, (final - inicial) / (double)CLOCKS_PER_SEC);
        free(vetor_quick);

        // Heap:
        inicial = clock();
        heapsort(vetor_heap, tamanho);
        final = clock();
        fprintf(heap, "%d,%d,%d,%lf\n", modo, tamanho, i + 1, (final - inicial) / (double)CLOCKS_PER_SEC);
        free(vetor_heap);
    }
}

void gerar_vetores(int modo, int tamanho, int **ptr1, int **ptr2, int **ptr3, int **ptr4, int **ptr5)
{
    int *vetor1 = (int *) malloc(tamanho * sizeof(int));
    int *vetor2 = (int *) malloc(tamanho * sizeof(int));
    int *vetor3 = (int *) malloc(tamanho * sizeof(int));
    int *vetor4 = (int *) malloc(tamanho * sizeof(int));
    int *vetor5 = (int *) malloc((tamanho + 1) * sizeof(int)); // Vetor especial heap.

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
        vetor4[i] = vetor1[i];
        vetor5[i + 1] = vetor1[i];
    }

    vetor5[0] = -1;

    *ptr1 = vetor1;
    *ptr2 = vetor2;
    *ptr3 = vetor3;
    *ptr4 = vetor4;
    *ptr5 = vetor5;
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

/******************************************************************************
 *               ALGORITMOS DE ORDENAÇÃO: Quick Sort, Heap Sort               *
 ******************************************************************************/

void quicksort(int* v, int ini, int fim)
{
    if (fim <= ini) return;

    int p = ini;
    int i = ini + 1;
    int j = fim; 
    
    while (i <= j)
    {
        while (i <= fim && v[i] <= v[p]) i++;
        while (v[j] > v[p]) j--;

        if (j > i)
        {
            int temp = v[i];
            v[i] = v[j];
            v[j] = temp;
        }
    }

    p = j;
    int temp = v[p];
    v[p] = v[ini];
    v[ini] = temp;

    quicksort(v, ini, p - 1);
    quicksort(v, p + 1, fim);
}

void max_heapify(int *v, int p, int N)
{
    int f = p * 2;

    if (f > N) return;

    if (v[f] > v[p] || (f + 1 <= N && v[f + 1] > v[p]))
    {
        if (f + 1 <= N && v[f + 1] > v[f])
            f = f + 1;

        int tmp = v[p];
        v[p] = v[f];
        v[f] = tmp;

        max_heapify(v, f, N);
    }
}

void build_maxheap(int *v, int N)
{
    int m = N / 2;

    for (int p = m; p >= 1; p--)
    {
        max_heapify(v, p, N);
    }
}

void heapsort(int *v, int N)
{
    if (N < 1)
        return;

    build_maxheap(v, N);

    while (N >= 2)
    {
        int maior = v[1];
        v[1] = v[N];
        v[N] = maior;

        N--;

        max_heapify(v, 1, N);
    }
}