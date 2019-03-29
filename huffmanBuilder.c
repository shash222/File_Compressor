#include "fileCompressor.h"

char* getCode(node n, char* c, int fd){
    char code[strlen(c) + 1];
    char cd[strlen(c) + 1];

    // char* version of line to be printed
    // 2 is size of \t and \n
    char printLine[strlen(cd) + 2 + strlen(n.word) + 2];
    strcpy(printLine, c);
    strcat(strcat(strcat(printLine, "\t"), n.word), "\n");
    void* buffer = (void*) printLine;

    if(n.left == NULL && n.right == NULL)  write(fd, buffer, strlen(buffer));//printf("%s\t%s\n", c, n.word);
    strcpy(code, c);
    strcpy(cd, code);
    if (n.left != NULL) getCode(*(n.left), strcat(code,"0"), fd);
    if (n.right != NULL) getCode(*(n.right), strcat(cd,"1"), fd);
}

char* getHuffmanCode(node n){
    char c[1] = "";
    int fd = creat("HuffmanCodebook", 0777);
    return getCode(n, c, fd);
}

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
        node* subtree = (node*) malloc(sizeof(node));
        *subtree = getSubtree();
        insert(subtree);
    }
    // printHuffman(*head);
    getHuffmanCode(*head);
}