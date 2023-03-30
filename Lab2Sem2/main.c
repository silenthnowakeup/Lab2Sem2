#include "functions.h"

int main() {
    FILE* file;

    DblLinkedList* list;
    list = (DblLinkedList*)malloc(sizeof(DblLinkedList));

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    if ((file = fopen("D:/Lab2Sem2/cmake-build-debug/test1.txt", "r")) == NULL) {
        printf("Error\n");
        exit(1);
    }

    wordInfo(file, list);


    fclose(file);

    listInfo(list);
    FILE *compressedFile;

    if ((file = fopen("D:/Lab2Sem2/cmake-build-debug/test1.txt", "r")) == NULL) {
        printf("Error\n");
        exit(1);
    }

    if ((compressedFile = fopen("D:/Lab2Sem2/cmake-build-debug/compFile.txt", "w")) == NULL) {
        printf("Error\n");
        exit(1);
    }

    int numReplacements = 0;
    char **wordsA = (char **) malloc(list->size * sizeof(char *));
    char **wordsB = (char **) malloc(list->size * sizeof(char *));

    while (1) {
        int indPop = findPopularWord(list, (int) list->size);
        int indRare = findRarityWord(list, (int) list->size);

        if (checkVigoda(list, indPop, indRare) == 1) {
            char *wordA = (char *) malloc(at(list, indPop)->length * sizeof(char));
            char *wordB = (char *) malloc(at(list, indRare)->length * sizeof(char));
            strcpy(wordA, at(list, indPop)->text);
            strcpy(wordB, at(list, indRare)->text);
            wordsA[numReplacements] = wordA;
            wordsB[numReplacements] = wordB;
            numReplacements++;
            removeNode(list, wordA);
            removeNode(list, wordB);
        } else {
            break;
        }
    }

    printDollar(compressedFile,wordsA,wordsB,numReplacements);

    printCompressedFile(file,compressedFile, wordsA, wordsB, numReplacements);

    fclose(file);
    fclose(compressedFile);
    return 0;
}
