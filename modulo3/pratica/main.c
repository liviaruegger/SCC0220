/**
 * @file   main.c
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

int main()
{
    char *string;
    scanf("%m[^\n]", &string);

    node_t *huffman_tree;
    char *encoded_string = huffman_encode(string, &(huffman_tree));
    char *decoded_string = huffman_decode(encoded_string, huffman_tree);

    if (strcmp(string, decoded_string) != 0)
    {
        printf("Erro na decodificação!\n");
    }
    else
    {
        printf("%s\n", decoded_string);
        
        // Calcula o índice de compressão:
        float ratio = (float)strlen(encoded_string) / (8.0 * strlen(string));
        printf("Indice de compressao: %.2f\n", ratio);
    }
    
    free(string);
    free(encoded_string);
    free(decoded_string);
    destroy_huffman_tree(huffman_tree);

    return 0;
}