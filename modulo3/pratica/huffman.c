/**
 * @file   huffman.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0220 - Laboratório de Introdução à Ciência da Computação II
 *         Módulo 3: Codificação de Huffman (terceira implementação prática)
 *         
 * @date   2021-12-23
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

struct huffman_node
{
    char data;
    int freq;
    node_t *left;
    node_t *right;
};

typedef struct minheap
{
    int size;
    node_t **array;
}   minheap_t;

static int *create_alphabet(char *string);
static minheap_t *create_min_heap(int *alphabet);
static node_t *create_node(char data, int freq);
static void build_min_heap(minheap_t *min_heap);
static void min_heapify(minheap_t *min_heap, int i);
static node_t *build_huffman_tree(minheap_t *min_heap);
static node_t *extract_min(minheap_t *min_heap);
static void insert_min_heap_node(minheap_t *min_heap, node_t *new_node);
static char **create_code_table();
static void build_code_table(char **table, node_t *root, char buffer[], int code_size);
static char *encode(char *string, char **code_table);
static void destroy_code_table(char **code_table);
static char decode_char(char *encoded_string, node_t *root, int *i);

/**
 * @brief A partir de uma string, constrói uma árvore de Huffman e realiza sua
 * codificação/compressão.
 * 
 * @param string cadeia de caracteres que deve ser codificada/comprimida; 
 * @param huffman_tree endereço onde será armazenado um ponteiro para a raiz da
 * árvore de Huffman (node_t *);
 * @return string codificada (char *). 
 */
char *huffman_encode(char *string, node_t **huffman_tree)
{
    int *alphabet = create_alphabet(string);
    minheap_t *min_heap = create_min_heap(alphabet);
    build_min_heap(min_heap);

    node_t *huffman_tree_root = build_huffman_tree(min_heap);

    char buffer[MAX_TREE_HEIGHT];
    char **code_table = create_code_table();
    build_code_table(code_table, huffman_tree_root, buffer, 0);

    char *encoded_string = encode(string, code_table);

    destroy_code_table(code_table);
    free(alphabet);
    free(min_heap->array);
    free(min_heap);

    *huffman_tree = huffman_tree_root;
    return encoded_string;
}

/**
 * @brief Cria um vetor de inteiros que representa o alfabeto referente ao
 * conjunto inicial de dados (string). Os índices do vetor são dados pelos
 * respectivos valores dos caracteres na tabela ASCII e seus elementos
 * representam a frequência de cada caractere na string.
 * 
 * @param string conjunto de dados a partir do qual será gerado o alfabeto;
 * @return vetor de inteiros representando o alfabeto (int *).
 */
static int *create_alphabet(char *string)
{
    int string_size = strlen(string);

    int *count = (int *) calloc(ALPHABET_SIZE, sizeof(int));

    for (int i = 0; i < string_size; i++)
        count[string[i]]++;

    return count;
}

/**
 * @brief A partir de um alfabeto, cria um conjunto de nós, cada nó contendo
 * um caractere (representação visual) e sua respectiva frequência.
 * 
 * @param alphabet vetor de inteiros representando o alfabeto;
 * @return struct (minheap_t *) que guarda o conjunto de nós (node_t **) e o
 * tamanho total do conjunto (int).
 */
static minheap_t *create_min_heap(int *alphabet)
{
    minheap_t *min_heap = (minheap_t *) malloc(sizeof(minheap_t));
    min_heap->array = (node_t **) malloc(ALPHABET_SIZE * sizeof(node_t *));

    min_heap->size = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (alphabet[i]) // Se a frequência for 0, não precisa criar o nó.
        {
            min_heap->array[min_heap->size] = create_node(i, alphabet[i]);
            min_heap->size++;
        }
    }

    min_heap->array = (node_t **) realloc(min_heap->array, min_heap->size * sizeof(node_t *));

    return min_heap;
}

/**
 * @brief Cria um nó folha de árvore binária com as informações dadas.
 * 
 * @param data representação visual;
 * @param freq frequência;
 * @return ponteiro para o nó criado (node_t *).
 */
static node_t *create_node(char data, int freq)
{
    node_t *new_node = (node_t *) malloc(sizeof(node_t));

    new_node->data = data;
    new_node->freq = freq;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

/**
 * @brief Monta um heap mínimo no conjunto de nós da struct dada.
 * 
 * @param min_heap struct (minheap_t *) que guarda o conjunto de nós no qual
 * será montado o min heap (node_t **) e o tamanho total do conjunto (int).
 */
static void build_min_heap(minheap_t *min_heap)
{
    int n = (min_heap->size - 1) / 2; // Último nó pai.

    // Executa a função heapify do último nó pai para o início.
    for (int i = n; i >= 0; i--)
    {
        min_heapify(min_heap, i);
    }
}

/**
 * @brief Garante que um nó de árvore binária esteja em condição de min heap;
 * caso o nó seja movido, realiza uma chamada recursiva para a nova posição.
 * 
 * @param min_heap struct (minheap_t *) que guarda o conjunto de nós no qual
 * será montado o min heap (node_t **) e o tamanho total do conjunto (int);
 * @param i índice do nó que está sendo verificado.
 */
static void min_heapify(minheap_t *min_heap, int i)
{
    int i_least_frequent = i;
    int i_left = 2 * i + 1;
    int i_right = 2 * i + 2;
    
    if (i_left < min_heap->size
    && min_heap->array[i_left]->freq < min_heap->array[i_least_frequent]->freq)
        i_least_frequent = i_left;

    if (i_right < min_heap->size
    && min_heap->array[i_right]->freq < min_heap->array[i_least_frequent]->freq)
        i_least_frequent = i_right;

    if (i_least_frequent == i) return; // Já está na condição de min heap.

    // Troca os nós.
    node_t *temp = min_heap->array[i];
    min_heap->array[i] = min_heap->array[i_least_frequent];
    min_heap->array[i_least_frequent] = temp;

    min_heapify(min_heap, i_least_frequent);
}

/**
 * @brief A partir de um conjunto de nós já em estrutura de heap mínimo,
 * constrói uma árvore de Huffman.
 * 
 * @param min_heap struct (minheap_t *) que guarda o conjunto de nós em heap 
 * mínimo (node_t **) e o tamanho total do conjunto (int);
 * @return ponteiro para a raiz da árvore de Huffman (node_t *). 
 */
static node_t *build_huffman_tree(minheap_t *min_heap)
{
    node_t *parent, *left, *right;

    while (min_heap->size > 1)
    {
        left = extract_min(min_heap);
        right = extract_min(min_heap);

        // Para nós internos, adicionamos o valor '\0'.
        parent = create_node('\0', left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        insert_min_heap_node(min_heap, parent);
    }

    // O último nó é a raiz da árvore de Huffman.
    return extract_min(min_heap);
}

/**
 * @brief Extrai, do conjunto de nós em estrutura de heap mínimo, o nó que
 * contém o menor valor (frequência).
 * 
 * @param min_heap struct (minheap_t *) que guarda o conjunto de nós em heap 
 * mínimo (node_t **) e o tamanho total do conjunto (int);
 * @return ponteiro para o nó extraído do conjunto (node_t *). 
 */
static node_t *extract_min(minheap_t *min_heap)
{
    node_t *temp = min_heap->array[0];
    min_heap->array[0] = min_heap->array[--min_heap->size];

    min_heapify(min_heap, 0); // Reconstruir a estrutura heap.

    return temp;
}

/**
 * @brief Insere um novo nó no conjunto, respeitando a condição de heap mínimo.
 * 
 * @param min_heap struct (minheap_t *) que guarda o conjunto de nós em heap 
 * mínimo (node_t **) e o tamanho total do conjunto (int);
 * @param new_node nó que deve ser inserido no conjunto.
 */
static void insert_min_heap_node(minheap_t *min_heap, node_t *new_node)
{
    int i = min_heap->size++; // Um nó folha será acrescentado.
    
    // Busca a posição correta de inserção.
    while (i > 0 && new_node->freq < min_heap->array[(i - 1) / 2]->freq)
    {
        min_heap->array[i] = min_heap->array[(i - 1) / 2]; // Desce o nó pai.
        i = (i - 1) / 2; // Atualiza i para a posição de nó pai.
    }
    
    min_heap->array[i] = new_node;
}

/**
 * @brief Cria uma tabela do tamanho do alfabeto e inicia todos os seus
 * elementos como NULL.
 * 
 * @return ponteiro para a tabela criada (char **). 
 */
static char **create_code_table()
{
    char **code_table = (char **) malloc(ALPHABET_SIZE * sizeof(char *));

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        code_table[i] = NULL;
    }

    return code_table;
}

/**
 * @brief Dada uma árvore de Huffman, constrói recursivamente uma tabela com
 * os códigos (em forma de string) associados a seus respectivos caracteres;
 * o valor do caractere é o índice do seu código na tabela.
 * 
 * @param table tabela de códigos do tamanho do alfabeto, vazia;
 * @param root ponteiro para a raiz da árvore de Huffman;
 * @param buffer vetor para armazenar temporariamente o código;
 * @param code_size quantidade de caracteres no código.
 */
static void build_code_table(char **table, node_t *root, char buffer[], int code_size)
{
    if (root->left)
    {
        buffer[code_size] = '0';
        build_code_table(table, root->left, buffer, code_size + 1);
    }

    if (root->right)
    {
        buffer[code_size] = '1';
        build_code_table(table, root->right, buffer, code_size + 1);
    }

    if (!root->left && !root->right)
    {
        char *code = (char *) malloc((code_size + 1) * sizeof(char));
        for (int i = 0; i < code_size; i++)
        {
            code[i] = buffer[i];
        }
        code[code_size] = '\0';
        table[root->data] = code;
    }
}

/**
 * @brief Codifica uma cadeia de caracteres segundo uma tabela de códigos.
 * 
 * @param string cadeia de caracteres que deve ser codificada/comprimida;
 * @param code_table tabela de códigos previamente construída a partir da
 * árvore de Huffman;
 * @return string codificada/comprimida (char *).
 */
static char *encode(char *string, char **code_table)
{
    char *char_code;
    char *encoded_str = NULL;
    int encoded_str_size = 0;
    int code_size;

    for (int i = 0; i < strlen(string); i++)
    {
        char_code = code_table[string[i]];
        code_size = strlen(char_code);
        
        encoded_str = (char *) realloc(encoded_str, (encoded_str_size + code_size) * sizeof(char));
        for (int i = 0; i < code_size; i++)
        {
            encoded_str[encoded_str_size++] = char_code[i];
        }
    }

    encoded_str = (char *) realloc(encoded_str, (encoded_str_size + 1) * sizeof(char));
    encoded_str[encoded_str_size] = '\0';
    
    return encoded_str;
}

/**
 * @brief Desaloca toda a memória ocupada por uma tabela de códigos.
 * 
 * @param code_table ponteiro para a tabela de códigos que deve ser destruída.
 */
static void destroy_code_table(char **code_table)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (code_table[i]) free(code_table[i]);
    }

    free(code_table);
}

/**
 * @brief Realiza a descompressão de uma string a partir da árvore de Huffman
 * que foi utilizada em sua codificação/compressão.
 * 
 * @param encoded_string string codificada/comprimida que deve ser decodificada;
 * @param huffman_tree ponteiro para a raiz da árvore de Huffman;
 * @return string descomprimida (char *). 
 */
char *huffman_decode(char *encoded_string, node_t *huffman_tree)
{
    int encoded_str_size = strlen(encoded_string);

    int buffer_size = 100;
    int decoded_str_size = 0;

    char *decoded_string = (char *) malloc(buffer_size * sizeof(char));

    int i = 0;
    while (i < encoded_str_size)
    {
        decoded_string[decoded_str_size++] = decode_char(encoded_string, huffman_tree, &i);

        if (decoded_str_size == buffer_size)
        {
            buffer_size += 50;
            decoded_string = (char *) realloc(decoded_string, buffer_size * sizeof(char));
        }
    }

    decoded_string[decoded_str_size] = '\0';
    decoded_string = (char *) realloc(decoded_string, (decoded_str_size + 1) * sizeof(char));

    return decoded_string;
}

/**
 * @brief Função recursiva que realiza, através da árvore de Huffman, a
 * decodificação de um único caractere codificado na string comprimida.
 * 
 * @param encoded_string cadeia de caracteres codificada/comprimida;
 * @param root nó atual da recursão (começando pela raiz da árvore);
 * @param i índice que percorre a string codificada;
 * @return caractere decodificado (char).
 */
static char decode_char(char *encoded_string, node_t *root, int *i)
{
    // Caso base: chegou na folha.
    if (!root->left && !root->right) return root->data;

    if (encoded_string[*i] == '0')
    {
        (*i)++;
        decode_char(encoded_string, root->left, i);
    }
    else if (encoded_string[*i] == '1')
    {
        (*i)++;
        decode_char(encoded_string, root->right, i);
    }
}

/**
 * @brief Desaloca a memória ocupada pela árvore de Huffman (árvore binária).
 * 
 * @param root nó atual da recursão (começando pela raiz da árvore).
 */
void destroy_huffman_tree(node_t *root)
{
    if (root)
    {
        destroy_huffman_tree(root->left);
        destroy_huffman_tree(root->right);
        free(root);
    }
}