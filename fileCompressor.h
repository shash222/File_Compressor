#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>


// heap.c method signatures
typedef struct{
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
