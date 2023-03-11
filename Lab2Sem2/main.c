
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

    file = fopen("D:/Lab2Sem2/cmake-build-debug/test1.txt", "r");
    int countWords = quantityWord(file);
    fclose(file);


    struct Word* words;
    words = (struct Word*)malloc(countWords * sizeof(struct Word));
    int wordsCount = 0;

    if ((file = fopen("D:/Lab2Sem2/cmake-build-debug/test1.txt", "r")) == NULL) {
        printf("Error\n");
        exit(1);
    }

    wordInfo(file, words, &wordsCount);

    /*int maxLength = maxWordLength(file,words,wordsCount);
    allocateText(words,wordsCount,maxLength);*/

    for (int i = 0; i < wordsCount; i++) {
        printf("%s(%d): %d\n", words[i].text, words[i].length, words[i].count);
    }


    fclose(file);



    findPopularWord(words,wordsCount);
    findRarityWord(words,wordsCount);


    char* wordA = (char*)malloc(words[findPopularWord(words,wordsCount)].length * sizeof(char));
    char* wordB = (char*)malloc(words[findRarityWord(words,wordsCount)].length * sizeof(char));;


    strcpy(wordA, words[findPopularWord(words,wordsCount)].text);
    strcpy(wordB, words[findRarityWord(words,wordsCount)].text);

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


    printCompressedFile(file,compressedFile, wordA, wordB);
    printDollar(compressedFile,wordA,wordB);

    fclose(file);
    fclose(compressedFile);

            return 0;
}
