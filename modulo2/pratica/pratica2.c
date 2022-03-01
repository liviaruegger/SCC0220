/**
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0220 - Laboratório de Introdução à Ciência da Computação II
 *         Módulo 2: Übersort (segunda implementação prática)
 *         
 * @date   2021-11-17
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define MEDIANA   1
#define ALEATORIO 2

void quicksort(int *v, int ini, int fim, int modo);
void insertion_sort(int *vetor, int ini, int fim);

int main()
{
    int tamanho, modo;
    scanf("%d", &tamanho);
    scanf("%d", &modo);

    int array[tamanho];
    for (int i = 0; i < tamanho; i++)
        scanf("%d", &array[i]);

    srand(42);
    quicksort(array, 0, tamanho - 1, modo);

    for (int i = 0; i < tamanho; i++)
        printf("%d\n", array[i]);
    
    return 0;
}

/**
 * @brief Quicksort com algumas otimizações para evitar cair no seu pior caso
 * para ordenação: implementação conjunta com o insertion sort para vetores de
 * tamanho menor ou igual a dez, dois métodos possíveis para escolha do pivô
 * (randômico ou mediana entre três elementos) e divisão em três grupos em vez
 * de dois (elementos menores, iguais e maiores que o pivô).
 * 
 * @param v vetor que será ordenado;
 * @param ini índice do início da parte sendo ordenada na chamada atual;
 * @param fim índice do fim da parte sendo ordenada na chamada atual;
 * @param modo modo de escolha do pivô: 1 para mediana, 2 para aleatório.
 */
void quicksort(int *v, int ini, int fim, int modo)
{
    // 1. Caso base ============================================================
    if (fim <= ini) return;
    
    // Otimização: para vetores de tamanho <= 10, ordena utilizando o insertion
    // sort e encerra a recursão.
    if (fim - ini < 10)
    {
        insertion_sort(v, ini, fim);
        return;
    }

    // 2. Partição ao redor de um pivô =========================================
    
    // Seleção do pivô ---------------------------------------------------------
    // Otimização: para evitar cair no pior caso, adota dois métodos possíveis
    // para a escolha do pivô: escolhe a mediana entre o primeiro elemento, o
    // elemento do meio e o último elemento, ou escolhe um pivô aleatoriamente.

    int p;
    if (modo == MEDIANA) // Método 1: mediana de três
    {
        int meio = ((fim - ini) / 2) + ini;

        if (v[meio] < v[fim])
            p = v[ini] < v[meio] ? meio : (v[ini] < v[fim] ? ini : fim);
        else
            p = v[ini] < v[fim] ? fim : (v[ini] < v[meio] ? ini : meio);
    }
    else if (modo == ALEATORIO) // Método 2: pivô aleatório
    {
        p = (rand() % (fim - ini + 1)) + ini;
    }

    // Colocar o pivo escolhido no fim.
    int temp = v[fim];
    v[fim] = v[p];
    v[p] = temp;
    p = fim;

    // Realizar trocas ---------------------------------------------------------
    // Otimização: em vez de separar os elemntos do array em dois grupos, separa
    // em três: menores que o pivô, maiores que o pivô e iguais ao pivô, de tal
    // forma que todos os elementos iguais ao pivô já ficarão posicionados
    // corretamente e não entrarão na próxima chamada recursiva. 

    int i = ini;     // Delimita a lista à esquerda (valores < p).
    int j = fim - 1; // Delimita a lista à direita  (valores > p).
    int k = i;       // Percorre o meio, posicionando os valores na lista certa.

    while (k <= j)
    {
        if (v[k] > v[p])
        {
            temp = v[k];
            v[k] = v[j];
            v[j] = temp;
            
            j--;
        }
        else if (v[k] < v[p])
        {
            temp = v[k];
            v[k] = v[i];
            v[i] = temp;

            i++;
            k++;
        }
        else if (v[k] == v[p])
        {
            k++;
        }
    }

    // Posicionar o pivô definitivamente ---------------------------------------
    p = k;
    temp = v[p];
    v[p] = v[fim];
    v[fim] = temp;

    // 3. Chamadas recursivas ==================================================
    quicksort(v, ini, i - 1, modo); // Chamada para a lista à esquerda.
    quicksort(v, p + 1, fim, modo); // Chamada para a lista à direita.
}

/**
 * @brief Insertion sort adaptado para ordenar apenas uma seção específica do
 * vetor recebido. 
 * 
 * @param vetor vetor cuja parte será ordenada;
 * @param ini índice do início da seção que será ordenada;
 * @param fim índice do fim da seção que será ordenada.
 */
void insertion_sort(int *vetor, int ini, int fim)
{
    for (int j = ini + 1; j <= fim; j++)
    {
        int chave = vetor[j];
        int i = j - 1;
        while (i >= ini && vetor[i] > chave)
        {
            vetor[i + 1] = vetor[i];
            i--;
        }
        vetor[i + 1] = chave;
    }
}