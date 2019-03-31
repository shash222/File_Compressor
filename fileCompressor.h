#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

// heap.c method signatures
typedef struct node{
    char* word;
    int freq;
    struct node* left;
    struct node* right;
} node;


node* head;

int firstAvailable;
int sizeOfArray;


node removeMin();

void insert(node* n);

void printHeap();

void createHeap();


// hashmap.c method signatures





//huffmanBuilder.c method signatures
void getCode(node n, char* c, int fd);

void getHuffmanCode(node n);

node getSubtree();

void createHuffmanTree();

void readBook();

void compressString(char* file);

void decompressString(char* file);
