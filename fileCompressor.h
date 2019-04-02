#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

// hashtable.c method signatures
#define size 10000
#define key 0

typedef struct tableNode{
  int freq;
  char * word;
  struct tableNode *next;

}tableNode;

int tableSize;

struct tableNode* tableHead;

void insertIntoTable(char* str);

int searchTable(char * str);

void printTable();


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



//huffmanBuilder.c method signatures
void getCode(node n, char* c, int fd);

void getHuffmanCode(node n);

node getSubtree();

void createHuffmanTree();

void createPairsArray();

void compressFile(char* path);

void decompressFile(char* path);
