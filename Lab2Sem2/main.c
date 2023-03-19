#include "functions.h"

int main() {
    char s;
    FILE* file;

    if ((file = fopen("D:/Lab2Sem2/cmake-build-debug/test1.txt", "w")) == NULL) {
        printf("Error\n");
        exit(1);
    }

    printf("Enter some text: ");

    while ((s = getchar()) != '\n') {
        fputc(s, file);
    }

    fclose(file);

    DblLinkedList* list;
    list = (DblLinkedList*)malloc(sizeof(DblLinkedList));

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    int wordsCount = 0;

    if ((file = fopen("D:/Lab2Sem2/cmake-build-debug/test1.txt", "r")) == NULL) {
        printf("Error\n");
        exit(1);
    }

    wordInfo(file, list, &wordsCount);

    /*int maxLength = maxWordLength(file,words,wordsCount);
    allocateText(words,wordsCount,maxLength);*/

    fclose(file);

    listInfo(list);

    int indPop = findPopularWord(list, list->size);
    int indRare = findRarityWord(list, list->size);
    printf("\nhello %d,%d\n", indPop,indRare);


    char* wordA = (char*)malloc(at(list, indPop)->length * sizeof(char));
    char* wordB = (char*)malloc(at(list, indRare)->length * sizeof(char));;


    strcpy(wordA, at(list, indPop)->text);
    strcpy(wordB, at(list, indRare)->text);

    if ((file = fopen("D:/Lab2Sem2/cmake-build-debug/test1.txt", "r")) == NULL)
    {
        printf("Error\n");
        exit(1);
    }

    FILE* compressedFile;
    if ((compressedFile = fopen("D:/Lab2Sem2/cmake-build-debug/compFile.txt", "w")) == NULL)
    {
        printf("Error\n");
        exit(1);
    }


    printCompressedFile(file, compressedFile, wordA, wordB);
    printDollar(compressedFile, wordA, wordB);

    fclose(file);
    fclose(compressedFile);

    return 0;
}
