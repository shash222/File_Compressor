#include "fileCompressor.h"

node* head;

// Refers to first empty index in head array
int firstAvailable = 0;

void printHeap(){
    int i;
    for (i = 0; i < firstAvailable; i++){
        printf("%s %d\n", head[i].word, head[i].freq);
    }
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
    head[firstAvailable] = *n;
    firstAvailable++;
    // printf("abc%s %d %s %d %s %d\n", n -> word, n -> freq, n -> left ->word, n -> left -> freq, n -> right -> word, n -> right -> freq);
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
    tableNode* table = tableHead;
    head = (node*) calloc(tableSize, sizeof(node));
    int i;
    node n;
    while(table != NULL){
        n.word = table -> word;
        n.freq = table -> freq;
        n.left = NULL;
        n.right = NULL;
        insert(&n);
        table = table -> next;
    }
}
