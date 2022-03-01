/**
 * @file   huffman.h
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0220 - Laboratório de Introdução à Ciência da Computação II
 *         Módulo 3: Codificação de Huffman (terceira implementação prática)
 *         
 * @date   2021-12-23
 * 
 */

#define ALPHABET_SIZE 256
#define MAX_TREE_HEIGHT 8

typedef struct huffman_node node_t;

char *huffman_encode(char *string, node_t **huffman_tree);
char *huffman_decode(char *string, node_t *huffman_tree);
void destroy_huffman_tree(node_t *root);