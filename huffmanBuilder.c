#include "fileCompressor.h"

void printHuffman(node n){
    printf("%s %d\n", n.word, n.freq);
    if (n.left != NULL) printHuffman(*(n.left));
    if (n.right != NULL) printHuffman(*(n.right));
}

node getSubtree(){
    node* left = (node*) malloc(sizeof(node));
    node* right = (node*) malloc(sizeof(node));
    *left = removeMin();
    *right = removeMin();
    node subtree = {"", left -> freq + right -> freq, left, right};
    return subtree;
}

void createHuffmanTree(){
    while(firstAvailable > 1){
        node* subtree = (node *) malloc(sizeof(node));
        *subtree = getSubtree();
        insert(subtree);
    }
    printHuffman(*head);
}