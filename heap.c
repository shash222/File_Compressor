#include "fileCompressor.h"
/*

USE AN ARRAY OF STRUCT NODES, FORGET ABOUT SUBTREE CHILDREN, AS THEY ARE GOING TO BE STORED IMPLICITLY BY TREE HEAD NODE. 

ORIGINALLY, NO WORD IS GOING TO HAVE A RIGHT OR LEFT CHILD, THESE CHILDREN ONLY ARE USED FOR THE SUBTREES WITH HEAD NODE STORING FREQUENCY AND EMPTY STRING

*/

node* head;

// Refers to first empty index in head array
int firstAvailable = 0;
int sizeOfArray = 11;

void printHeap(){
    for (int i = 0; i < firstAvailable; i++){
        printf("%s %d\n", head[i].word, head[i].freq);
    }
}

//Doubles size of heap array if capacity has been reached
void increaseArray(){
    sizeOfArray *= 2;
    node* temp = (node*) realloc(head, sizeOfArray);
    if (temp != NULL) head = temp;
    else printf("More memory cannot be reallocated!\n");
    free(temp);
}

//sorts heap into min heap after insertion
void heapSortInsertion(){
    int curr = firstAvailable - 1;
    node c, p;
    int j = 0;
    do{
        if (curr == 0) return;
        // Child node
        c = head[curr];

        // Parent node
        p = head[(curr - 1) / 2];
        if (c.freq < p.freq){
            head[curr] = p;
            head[(curr - 1) / 2] = c;
        }
        curr = (curr - 1) / 2;
    }while(c.freq < p.freq);
}

//sorts heap into min heap after removing min
void heapSortDeletion(){

    // only 1 item in heap, no need to sort
    if (firstAvailable == 1) return;
  
    // curr refers to index of node that needs to be sifted down
    // after min is delted, last element in heap is placed in the first spot, which is being sifted down
    int curr = 0;
    node temp = head[0];
    // loop runs forever
    int minIndex;
    int left;
    int right;
    for(;;){
        left = 2 * curr + 1;
        right = 2 * curr + 2;
        if (left >= firstAvailable) break;
        minIndex = right >= firstAvailable 
            ? left
            : head[left].freq <= head[right].freq 
                ? left 
                : right;
        if (temp.freq <= head[minIndex].freq) break;
        head[curr] = head[minIndex];
        head[minIndex] = temp;
        curr = minIndex;
    }
}

void insert(node* n){
    if (firstAvailable == sizeOfArray){
        increaseArray();
    }
    head[firstAvailable] = *n;
    firstAvailable++;
    heapSortInsertion();
}

node removeMin(){
    if (firstAvailable == 0){
        node temp = {};
        return temp;
    }
    node removed = head[0];
    head[0] = head[firstAvailable - 1];
    heapSortDeletion();
    firstAvailable--;
//    printHeap();
    return removed;
}


void createHeap(){
    head = (node*) calloc(sizeOfArray, sizeof(node));
    int i;

    node a = {"a", 5};
    node b = {"dog", 9};
    node c = {"cat", 12};
    node d = {"button", 13};
    node e = {"ball", 16};
    node f = {"and", 45};
    // node g = {"and1", 45};
    // node h = {"and2", 45};
    // node i = {"and3", 45};
    // node j = {"and4", 45};
    // node k = {"and5", 45};
    // node l = {"and6", 45};
    node arr[6] = {c, a, e, d, b, f};
    int m;
    for (m = 0; m < (sizeof(arr)/sizeof(arr[0])); m++){
        insert(&arr[m]);
    }
    // for (m = 0; m < (sizeof(arr)/sizeof(arr[0])); m++){
    //     //printHeap();
    //     printf("%s\n", removeMin() -> word);
    //     printf("\n\n");
    // }
}
