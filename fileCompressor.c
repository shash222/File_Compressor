#include "fileCompressor.h"


void buildCodebook(char* path){
    int fd = open(path, 0);
    char word[25];
    strcpy(word, "");
    char c[2];
    strcpy(c, " ");
    while(read(fd, c, 1) != 0){
        // printf("%s\n", c);
        if((strcmp(c, " ") == 0) || (strcmp(c, "\n") == 0) || (strcmp(c, "\t") == 0)){
            insertIntoTable(strdup(word));
            strcpy(word, "");
        }
        else{
            strcat(word,c);
        }
    }
    insertIntoTable(strdup(word));
    close(fd);
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
    if (directory == NULL) return;
//     char command[50];
//    strcpy( command, "find data/  -exec cat {} \; > uber.json" );
    struct dirent* dir;
    while((dir = readdir(directory)) != NULL){
        char* file = (char*) calloc(sizeof(path) + sizeof(dir -> d_name), sizeof(char) + 1);
        if (path[strlen(path) - 1] != '/') strcat(path, "/");
        strcpy(file, path);
        strcat(file, dir -> d_name);
       // printf("%s\n", file);
        if(strcmp(dir -> d_name, ".") != 0 && strcmp(dir -> d_name, "..") != 0){
            getFiles(file, op);
            if (file[strlen(file) - 1] != '/'){
                if (op == 'b'){
                    buildCodebook(file);
                }
                else if (op == 'c'){
                    comp(file);
                }
                else if (op == 'd'){
                    decomp(file);
                }
            }
        }
        free(file);
    }
    if (op == 'b'){
        createHeap();
        createHuffmanTree();
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
        if (build != 0){
            buildCodebook(path);
            createHeap();
            createHuffmanTree();
        }
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
    return 0;
}
