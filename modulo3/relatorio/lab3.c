#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MODO 0 // Trocar para o modo desejado (opções abaixo).

#define ALEATORIO 0
#define  ORDENADO 1
#define INVERTIDO 2

// Definir amplitude de valores no vetor gerado aleatoriamente:
//#define AMPLITUDE_DE_VALORES 10000 // TESTE 1
//#define AMPLITUDE_DE_VALORES 100000 // TESTE 2
#define AMPLITUDE_DE_VALORES tamanho // TESTE 3
//#define AMPLITUDE_DE_VALORES tamanho * 2 // TESTE 4
//#define AMPLITUDE_DE_VALORES tamanho * 5 // TESTE 5
//#define AMPLITUDE_DE_VALORES tamanho * 10 // TESTE 6

typedef struct registro
{
    int chave;
    // Outros atributos
    // (...)
}   registro_t;

typedef struct no
{
    registro_t elem;
    struct no *prox;
}   no_t;

typedef struct balde
{
    no_t *inicio;
    no_t *fim;
}   balde_t;

void testar(int modo, int tamanho, FILE *bubble, FILE *insertion, FILE *merge, FILE *quick, FILE *heap, FILE *counting, FILE *bucket, FILE *radix);
void gerar_vetores(int modo, int tamanho, int **ptr1, int **ptr2, int **ptr3, int **ptr4, int **ptr5, registro_t **ptr6, registro_t **ptr7, registro_t **ptr8);
void imprimir_vetor(int* vetor, int tamanho_vetor);
void imprimir_vetor_reg(registro_t *vetor, int tamanho_vetor);

void bubbleSort(int *vetor, int tamanho);
void insertionSort(int *vetor, int tamanho);
void intercala(int *vetor, int inicio, int centro, int fim);
void mergeSort(int *vetor, int inicio, int fim);

void quicksort(int* v, int ini, int fim);
void max_heapify(int *v, int p, int N);
void build_maxheap(int *v, int N);
void heapsort(int *v, int N);

void counting_sort(registro_t *vetor, int tamanho);
void bucket_sort(registro_t *vetor, int tamanho);
void radix_sort(registro_t *vetor, int tamanho);


int main()
{
    // Criar arquivos.
    FILE *bubble_fp    = fopen("bubble.csv", "w");
    FILE *insertion_fp = fopen("insertion.csv", "w");
    FILE *merge_fp     = fopen("merge.csv", "w");
    FILE *quick_fp     = fopen("quick.csv", "w");
    FILE *heap_fp      = fopen("heap.csv", "w");
    FILE *counting_fp  = fopen("counting.csv", "w");
    FILE *bucket_fp    = fopen("bucket.csv", "w");
    FILE *radix_fp     = fopen("radix.csv", "w");

    // Escrever cabeçalhos.
    fprintf(bubble_fp,    "vector_type,vector_size,iteration,execution_time\n");
    fprintf(insertion_fp, "vector_type,vector_size,iteration,execution_time\n");
    fprintf(merge_fp,     "vector_type,vector_size,iteration,execution_time\n");
    fprintf(quick_fp,     "vector_type,vector_size,iteration,execution_time\n");
    fprintf(heap_fp,      "vector_type,vector_size,iteration,execution_time\n");
    fprintf(counting_fp,  "vector_type,vector_size,iteration,execution_time\n");
    fprintf(bucket_fp,    "vector_type,vector_size,iteration,execution_time\n");
    fprintf(radix_fp,     "vector_type,vector_size,iteration,execution_time\n");

    /* // TESTES 1-6 (counting, bucket, radix + quick, heap, merge)
    testar(MODO,     25, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,    100, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,    500, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,   1000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,   2500, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,   5000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,   7500, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  10000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  15000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  20000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  25000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  30000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  35000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  40000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  45000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  50000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  55000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  60000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  65000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  70000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  75000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  80000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  85000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  90000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO,  95000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(MODO, 100000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    */

    // TESTE 7 (pior caso)
    testar(ALEATORIO, 1000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar( ORDENADO, 1000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);
    testar(INVERTIDO, 1000, bubble_fp, insertion_fp, merge_fp, quick_fp, heap_fp, counting_fp, bucket_fp, radix_fp);

    // Fechar arquivos.
    fclose(bubble_fp);
    fclose(insertion_fp);
    fclose(merge_fp);
    fclose(quick_fp);
    fclose(heap_fp);

    return 0;
}


void testar(int modo, int tamanho, FILE *bubble, FILE *insertion, FILE *merge, FILE *quick, FILE *heap, FILE *counting, FILE *bucket, FILE *radix)
{
    clock_t inicial, final;

    for (int i = 0; i < 10; i++)
    {
        int *vetor_bubble    = NULL;
        int *vetor_insertion = NULL;
        int *vetor_merge     = NULL;
        int *vetor_quick     = NULL;
        int *vetor_heap      = NULL;

        registro_t *vetor_counting = NULL;
        registro_t *vetor_bucket   = NULL;
        registro_t *vetor_radix    = NULL;

        gerar_vetores(modo, tamanho, &vetor_bubble, &vetor_insertion, &vetor_merge, &vetor_quick, &vetor_heap, &vetor_counting, &vetor_bucket, &vetor_radix);

        // Bubble:
        //inicial = clock();
        //bubbleSort(vetor_bubble, tamanho);
        //final = clock();
        //fprintf(bubble, "%d,%d,%d,%lf\n", modo, tamanho, i + 1, (final - inicial) / (double)CLOCKS_PER_SEC);
        free(vetor_bubble);

        // Insertion:
        //inicial = clock();
        //insertionSort(vetor_insertion, tamanho);
        //final = clock();
        //fprintf(insertion, "%d,%d,%d,%lf\n", modo, tamanho, i + 1, (final - inicial) / (double)CLOCKS_PER_SEC);
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

        // Counting:
        inicial = clock();
        counting_sort(vetor_counting, tamanho);
        final = clock();
        fprintf(counting, "%d,%d,%d,%lf\n", modo, tamanho, i + 1, (final - inicial) / (double)CLOCKS_PER_SEC);
        free(vetor_counting);

        // Bucket:
        inicial = clock();
        bucket_sort(vetor_bucket, tamanho);
        final = clock();
        fprintf(bucket, "%d,%d,%d,%lf\n", modo, tamanho, i + 1, (final - inicial) / (double)CLOCKS_PER_SEC);
        free(vetor_bucket);

        // Radix:
        inicial = clock();
        radix_sort(vetor_radix, tamanho);
        final = clock();
        fprintf(radix, "%d,%d,%d,%lf\n", modo, tamanho, i + 1, (final - inicial) / (double)CLOCKS_PER_SEC);
        free(vetor_radix);
    }
}

void gerar_vetores(int modo, int tamanho, int **ptr1, int **ptr2, int **ptr3, int **ptr4, int **ptr5, registro_t **ptr6, registro_t **ptr7, registro_t **ptr8)
{
    int *vetor1 = (int *) malloc(tamanho * sizeof(int));
    int *vetor2 = (int *) malloc(tamanho * sizeof(int));
    int *vetor3 = (int *) malloc(tamanho * sizeof(int));
    int *vetor4 = (int *) malloc(tamanho * sizeof(int));
    int *vetor5 = (int *) malloc((tamanho + 1) * sizeof(int)); // Vetor especial heap.

    registro_t *vetor6 = (registro_t *) malloc(tamanho * sizeof(registro_t)); // Counting
    registro_t *vetor7 = (registro_t *) malloc(tamanho * sizeof(registro_t)); // Bucket
    registro_t *vetor8 = (registro_t *) malloc(tamanho * sizeof(registro_t)); // Radix

    for (int i = 0; i < tamanho; i++)
    {
        if (modo == ALEATORIO)
            vetor1[i] = rand() % (AMPLITUDE_DE_VALORES);
        else if (modo == ORDENADO)
            vetor1[i] = i;
        else if (modo == INVERTIDO)
            vetor1[i] = tamanho - i;

        vetor2[i] = vetor1[i];
        vetor3[i] = vetor1[i];
        vetor4[i] = vetor1[i];
        vetor5[i + 1] = vetor1[i];

        vetor6[i].chave = vetor1[i];
        vetor7[i].chave = vetor1[i];
        vetor8[i].chave = vetor1[i];
    }

    vetor5[0] = -1;

    *ptr1 = vetor1;
    *ptr2 = vetor2;
    *ptr3 = vetor3;
    *ptr4 = vetor4;
    *ptr5 = vetor5;

    *ptr6 = vetor6;
    *ptr7 = vetor7;
    *ptr8 = vetor8;
}

void imprimir_vetor(int *vetor, int tamanho_vetor)
{
    for (int i = 0; i < tamanho_vetor; i++)
        printf("%i ", vetor[i]);
    printf("\n");
}

void imprimir_vetor_reg(registro_t *vetor, int tamanho_vetor)
{
    for (int i = 0; i < tamanho_vetor; i++)
        printf("%i ", vetor[i].chave);
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

/******************************************************************************
 *      ALGORITMOS DE ORDENAÇÃO: Counting Sort, Bucket Sort, Radix Sort       *
 ******************************************************************************/

void counting_sort(registro_t *vetor, int tamanho)
{
    registro_t *copia = (registro_t *)malloc(tamanho * sizeof(registro_t));

    int max, min;
    max = min = vetor[0].chave;
    for (int i = 0; i < tamanho; i++)
    {
        if (vetor[i].chave > max)
            max = vetor[i].chave;
        if (vetor[i].chave < min)
            min = vetor[i].chave;
        copia[i] = vetor[i];
    }

    int k = max - min + 1;
    int *contagem = (int *)calloc(k, sizeof(int));

    for (int i = 0; i < tamanho; i++)
    {
        int posicao_chave = vetor[i].chave - min;
        contagem[posicao_chave]++;
    }

    int total = 0;
    for (int i = 0; i < k; i++)
    {
        int contagem_anterior = contagem[i];
        contagem[i] = total;
        total = total + contagem_anterior;
    }

    for (int i = 0; i < tamanho; i++)
    {
        int posicao_ordenada = contagem[copia[i].chave - min];
        vetor[posicao_ordenada] = copia[i];
        contagem[copia[i].chave - min]++;
    }

    free(contagem);
    free(copia);
}

void bucket_sort(registro_t *vetor, int tamanho)
{
    int max, min;
    max = min = vetor[0].chave;
    for (int i = 1; i < tamanho; i++)
    {
        if (vetor[i].chave > max)
            max = vetor[i].chave;
        if (vetor[i].chave < min)
            min = vetor[i].chave;
    }

    int k = max - min + 1;
    balde_t *baldes = (balde_t *)calloc(k, sizeof(balde_t));

    for (int i = 0; i < tamanho; i++)
    {
        int posicao_chave = vetor[i].chave - min;

        no_t *novo = malloc(sizeof(no_t));
        novo->elem = vetor[i];
        novo->prox = NULL;

        if (baldes[posicao_chave].inicio == NULL)
            baldes[posicao_chave].inicio = novo;
        else
            (baldes[posicao_chave].fim)->prox = novo;
        baldes[posicao_chave].fim = novo;
    }

    int j = 0;
    for (int i = 0; i < k; i++)
    {
        no_t *posicao;
        posicao = baldes[i].inicio;
        while (posicao != NULL)
        {
            vetor[j] = posicao->elem;
            j++;

            no_t *deletar = posicao;
            posicao = posicao->prox;
            baldes[i].inicio = posicao;
            free(deletar);
        }
    }

    free(baldes);
}

void radix_sort(registro_t *vetor, int tamanho)
{
    int contagem[256] = {0};
    int acumulada[256];
    
    registro_t *copia = (registro_t *)malloc(tamanho * sizeof(registro_t));

    int i, shift;
    for (shift = 0; shift <= 24; shift += 8) 
    {
        for (i = 0; i < tamanho; i++)
        {
            short k = (vetor[i].chave >> shift) & 255;
            contagem[k]++;
            copia[i] = vetor[i];
        }

        acumulada[0] = 0;
        for (i = 1; i < 256; i++)
        {
            acumulada[i] = acumulada[i - 1] + contagem[i - 1];
            contagem[i - 1] = 0;
        }

        for (i = 0; i < tamanho; i++)
        {
            short k = (copia[i].chave >> shift) & 255;
            vetor[acumulada[k]] = copia[i];
            acumulada[k]++;
        }
    }

    free(copia);
}