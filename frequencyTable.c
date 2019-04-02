#include "fileCompressor.h"

struct tableNode* tableHead;

void printTable(){
    tableNode* ptr = tableHead;
    while(ptr != NULL){
        printf("%s %d\n", ptr -> word, ptr -> freq);
        ptr = ptr -> next;
    }
}

void insertIntoTable(char* word){
    if (tableHead == NULL){
        tableHead = (tableNode*) malloc(sizeof(tableNode));
        tableHead -> word = word;
        tableHead -> freq = 1;
        tableHead -> next = NULL;
        tableSize = 1;
        return;
    }

    tableNode* ptr = tableHead;
    while(ptr -> next != NULL){
        if (strcmp(ptr -> word, word) == 0){
            ptr -> freq = (ptr -> freq) + 1;
            return;
        }
        ptr = ptr -> next;
    }
    if (strcmp(ptr -> word, word) == 0){
        ptr -> freq = (ptr -> freq) + 1;
        return;
    } 
    ptr -> next = (tableNode*) malloc(sizeof(tableNode));
    ptr -> next -> word = word;
    ptr -> next -> freq = 1;
    ptr -> next -> next = NULL;
    tableSize++;
}