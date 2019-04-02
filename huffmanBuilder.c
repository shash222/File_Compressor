#include "fileCompressor.h"

typedef struct pair{
    char* code;
    char* word;
}pair;

pair* pairs;
int numPairs;
// max characters in word when compressing
int maxCharacters;
// max digits in code when decompressing
int maxDigits;

char* findWord(char* code){
    int i;
    for (i = 0; i < numPairs; i++){
        if (strcmp(code, pairs[i].code) == 0){
            return pairs[i].word;
        }
    }
    //return empty string if word not found
    return "";
}

void decompressFile(char* file){
    // file descriptor for file to be read from
    int fd = open(file, 00);
    char newFile[strlen(file) - 3];
    strncpy(newFile, file, strlen(file) - 4);

    //for some reason newFile has proper value if the print statement is here
    // printf("%d %d %s %s\n", strlen(file), strlen(newFile), file, newFile);
    
    int fd2 = creat(newFile, 0777);
    char* c = (char*) calloc(2, sizeof(char));
    strcpy(c, "");
    while(read(fd, c, 1) != 0) maxDigits++;
    close(fd);
    fd = open(file, 00);
    char* code = (char*) calloc(maxDigits, sizeof(char));
    strcpy(code, "");
    int wordCount = 0;
    while(read(fd, c, 1) != 0){
        strcat(code, c);
        char* word = findWord(code);
        if(strcmp(word, "") != 0){
            if (wordCount++ != 0) write(fd2, " ", 1);
            write(fd2, word, strlen(word));
            strcpy(code, "");
        }
    }
    close(fd);
    close(fd2);
}

// writes code for single word into .hcz file of file to be compressed
void writeSingleCode(char* word, int fd){
    if (word == NULL) return;
    int i;
    for (i = 0; i < numPairs; i++){
        if(strcmp(pairs[i].word, word) == 0){
            write(fd, pairs[i].code, strlen(pairs[i].code));
        }
    }
}

void compressFile(char* file){
    int fd = open(file, 00);
    int characters = 0;
    int spaces = 0;
    char c[2] = "";
    while (read(fd, c, 1) != 0) {
        characters++;
        spaces++;
    }
    close(fd);
    char* input = (char*) calloc(spaces + 1, sizeof(char*));
    strcpy(input, "");
    fd = open(file, 00);
    int i;
    for (i = 0; i < characters; i++){
        read(fd, c, 1);
        strcat(input,c);
    }
    close(fd);
    // compressed file file descriptor
    char* newFile = strdup(file);
    fd = creat(strcat(newFile, ".hcz"), 0777);
    for(i = 0; i < spaces; i++){
        writeSingleCode(i == 0 ? strtok(input, " ") : strtok(NULL, " "), fd);
    }
}

// sets size of pairs array and value of maxCharacters
void assignValues(int fd){
    char* c = (char*) calloc(2, sizeof(char));
    strcpy(c, "");
    int newLines = 0;
    int characters = 0;
    for(;;){
        if (read(fd, c, 1) == 0) break;
        characters++;
        if (strcmp(c, "\n") == 0){
            newLines++;
            if (characters > maxCharacters) maxCharacters = characters;
            characters = 0;
        }
    }
    close(fd);
    numPairs = newLines;
    pairs = calloc(newLines, sizeof(pair));
}

void readFile(int fd){
    char* c = (char*) calloc(2, sizeof(char));
    strcpy(c, "");
    assignValues(open("HuffmanCodebook", 00));
    char* word = (char*) malloc(maxCharacters);
    strcpy(word, "");
    int count = 0;
    int pairsCount = 0;
    for(;;){
        if (read(fd, c, 1) == 0) break;
        if (strcmp(c, "\n") == 0){
            char* set = strtok(word, "\t");
            pair p;
            p.code = strdup(set);
            p.word = strdup(strtok(NULL, "\t"));
            pairs[pairsCount++] = p;
            strcpy(word, "");
        }
        else strcat(word, c);
        count++;
    }
}

void getCode(node n, char* c, int fd){
    char code[strlen(c) + 1];
    char cd[strlen(c) + 1];

    // char* version of line to be printed
    // 2 is size of \t and \n
    char printLine[strlen(cd) + 2 + strlen(n.word) + 2];
    strcpy(printLine, c);
    strcat(strcat(strcat(printLine, "\t"), n.word), "\n");
    void* buffer = (void*) printLine;

    if(n.left == NULL && n.right == NULL)  write(fd, buffer, strlen(buffer));
    strcpy(code, c);
    strcpy(cd, code);
    if (n.left != NULL) getCode(*(n.left), strcat(code,"0"), fd);
    if (n.right != NULL) getCode(*(n.right), strcat(cd,"1"), fd);
}

void getHuffmanCode(node n){
    char c[1] = "";
    int fd = creat("HuffmanCodebook", 0777);
    getCode(n, c, fd);
    // readFile(fd);
}


void printHuffman(node* n){
    printf("%s %d\n", n -> word, n -> freq);
    if (n -> left != NULL) printHuffman((n -> left));
    if (n -> right != NULL) printHuffman((n -> right));
}

node getSubtree(){
    node* left = (node*) malloc(sizeof(node));
    node* right = (node*) malloc(sizeof(node));
    *left = removeMin();
    *right = removeMin();
    node subtree = {"", left -> freq + right -> freq, left, right};
    // printf("%s %d %s %d %s %d\n", left -> word, left -> freq, right -> word, right -> freq, subtree. word, subtree.freq);
    return subtree;
}

void createHuffmanTree(){
    node* subtree = (node*) malloc(sizeof(node));
    while(firstAvailable > 1){
        *subtree = getSubtree();
        insert(subtree);
    }
    free(subtree);
    getHuffmanCode(*head);
}

void createPairsArray(){
    readFile(open("HuffmanCodebook", 00));
}
