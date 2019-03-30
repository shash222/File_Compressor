#include "fileCompressor.h"


int main(int argc, char** argv){
    int i;
    int build = 0;
    int compress = 0;
    int decompress = 0;
    int recursive = 0;
    for (i = 1; i < argc; i++){
        printf("%s\n", argv[i]);
        if (strcmp(argv[i], "-b")) build = 1;
        else if (strcmp(argv[i], "-c")) compress = 1;
        else if (strcmp(argv[i], "-d")) decompress = 1;
        else if (strcmp(argv[i], "-R")) recursive = 1;
    }
    // createHeap();
    // createHuffmanTree();
    readBook();
    char* file = "./testFiles/test1.txt"; 
    compressString(file);
    return 0;
}