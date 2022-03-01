/**
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0220 - Laboratório de Introdução à Ciência da Computação II
 *         Módulo 1: Ordenação Aconchegante (primeira implementação prática)
 *         
 * @date   2021-10-06
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 20 
#define MODO_TESTE   0 // Trocar por 1 para realizar o teste de tempo de execução.

typedef struct concha
{
    double diametro;
    char   *cor;
    char   *textura;
}   concha_t;

char *read_word(FILE *stream);
void ordenar_sublista(concha_t *lista, int tamanho, int i, int d);

int main()
{
    clock_t t1, t2;
    if (MODO_TESTE) t1 = clock();

    int n_conchas;
    scanf("%d", &n_conchas);
    getchar(); // Consome o quebra linha (\n).

    concha_t lista[n_conchas];

    for (int i = 0; i < n_conchas; i++)
    {
        scanf("%lf", &lista[i].diametro);
        getchar(); // Consome o quebra linha (\n).

        lista[i].cor     = read_word(stdin);
        lista[i].textura = read_word(stdin);
    }

    // Ordenação:
    int n = n_conchas/2;    
    while (n >= 1) 
    {
        // Passa por cada uma das sub-listas.
        for (int i = 0; i < n; i++)
            ordenar_sublista(lista, n_conchas, i, n);
        
        n /= 2;
    }

    for (int i = 0; i < n_conchas; i++)
        printf("%.3lf %s %s\n", lista[i].diametro, lista[i].cor, lista[i].textura);

    for (int i = 0; i < n_conchas; i++)
    {
        free(lista[i].cor);
        free(lista[i].textura);
    }
    
    if (MODO_TESTE)
    {
        t2 = clock();
        double tempo_execucao = (t2 - t1) / (double)CLOCKS_PER_SEC;
        printf("Tempo de execução: %.6lf segundo(s).\n", tempo_execucao);
    }

    return 0;
}

/**
 * @brief Alocando memória dinamicamente, lê e armazena uma palavra do arquivo dado até
 * encontrar um espaço, uma quebra de linha ou o fim do arquivo (EOF).
 * 
 * @param stream entrada (pode ser um arquivo ou a entrada padrão);
 * @return ponteiro para a string lida (char *). 
 */
char *read_word(FILE *stream)
{
    char *word = (char *) malloc(sizeof(char) * BUFFER_SIZE);
    int word_size = 0;
    int i = 1;

    do
    {
        word[word_size] = fgetc(stream);
        word_size++;

        if (word_size == BUFFER_SIZE * i)
        {
            i++;
            word = (char *) realloc(word, sizeof(char) * (i * BUFFER_SIZE));
        }

    } while (word[word_size - 1] != ' '  &&
             word[word_size - 1] != '\r' &&
             word[word_size - 1] != '\n' &&
             word[word_size - 1] != EOF);

    word[word_size - 1] = '\0';

    word = (char *) realloc(word, word_size);

    return word;
}

/**
 * @brief Insertion sort adaptado. A função será usada para ordenar uma sub-lista da
 * lista recebida como parâmetro.
 * 
 * @param lista vetor completo contendo todos os elementos (conchas);
 * @param tamanho tamanho do vetor completo;
 * @param i início da sub-lista (índice do seu primeiro elemento);
 * @param d distância entre cada elemento da sub-lista.
 */
void ordenar_sublista(concha_t *lista, int tamanho, int i, int d)
{	
	i += d; // Começa no segundo elemento da sub-lista.

	while (i < tamanho) 
    {
		concha_t comparar = lista[i]; // Fixa o elemento a ser comparado com anteriores.
		int j = i - d;                // Índice para percorrer elementos anteriores.

		while (j >= 0 && comparar.diametro < lista[j].diametro)
        {
			lista[j + d] = lista[j]; // Movimenta valor para frente na sub-lista.
			j -= d;                  // Índice retorna uma posição na sub-lista.
		}

		// Insere o elemento fixado na posição correta.
		lista[j + d] = comparar;

		i += d; // Avança para o próximo elemento da sub-lista.
	}
}