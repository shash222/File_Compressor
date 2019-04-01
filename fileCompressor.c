#include "fileCompressor.h"


void buildCodebook(char* path){
        printf("%s\n", path);
        int fd = open(path, 0);
        char* word = (char*) calloc(25, sizeof(char));
        char* dup;
        char c[2];
        strcpy(word, "");
        strcpy(c, "");
        int red = 0;
        int count = 0;
        // inserts words into hashtable
        while((red = read(fd, c, 1)) != 0){
            count+= red;
            // printf("%d %d %s\n", count, red, c);
            if (strcmp(c, " ") == 0 || strcmp(c, "\n") == 0 || strcmp(c, "\t") == 0){
                // printf("%s\n", word);
                dup = strdup(word);
                insertIntoTable(dup);
                strcpy(word, "");
            }
            else{
                strcat(word, c);
            }
        }
        // while loop does not insert last word into map
        insertIntoTable(word);

        // printTable();
        createHeap();
        // createHuffmanTree();
}


void decomp(char* path){
    createPairsArray();
    decompressFile(path);
}


void comp(char* path){
    createPairsArray();
    compressFile(path);
}

void getFiles(char* path, char op){
    DIR* directory = opendir(path);
    struct dirent* dir;
    while((dir = readdir(directory)) != NULL){
        char* file = (char*) calloc(sizeof(path) + sizeof(dir -> d_name), sizeof(char));
        if (path[strlen(path) - 1] != '/') strcat(path, "/");
        strcat(strcpy(file, path), dir -> d_name);
        if(strcmp(dir -> d_name, ".") != 0 && strcmp(dir -> d_name, "..") != 0){
            getFiles(file, op);
            if (file[strlen(file) - 1] != '/'){
                if (op == 'b') buildCodebook(file);
                else if (op == 'c'){
                    comp(file);
                }
                else if (op == 'd'){
                    decomp(file);
                }
            }
        } 
    }
    closedir(directory);
}

int main(int argc, char** argv){
    int i = 0;
    int build = 0;
    int compress = 0;
    int decompress = 0;
    int recursive = 0;
    char* arg;
    char* path;
    for (i = 1; i < argc; i++){
        arg = argv[i];
        if (strcmp(arg, "-b") == 0) build++;
        else if (strcmp(arg, "-c") == 0) compress++;
        else if (strcmp(arg, "-d") == 0) decompress++;
        else if (strcmp(arg, "-R") == 0) recursive++;
        else{
            path = argv[i];
            break;
        }
    }
    if (build == 0 && compress == 0 && decompress == 0 && recursive == 0){
        printf("No flags entered!");
        return 0;
    }
    
    // printf("%d %d %d\n", build, compress, decompress);

    if(recursive == 0){
        if (build != 0) buildCodebook(path);
        else if (compress != 0) comp(path);
        else if (decompress != 0) decomp(path);
    }
    else{
        char op;
        if (build != 0) op = 'b';
        else if (compress != 0) op = 'c';
        else if (decompress != 0) op = 'd';
        getFiles(path, op);
    }
    // createHeap();
    // createHuffmanTree();
    // readBook();
    // compressString(file);
    // decompressString("./testFiles/test1.txt.hcz");
    return 0;
}