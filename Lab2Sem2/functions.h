//
// Created by stasc on 11.03.2023.
//

#ifndef LAB2SEM2_FUNCTIONS_H
#define LAB2SEM2_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_WORD_LENGTH 50

struct Word {
    char text[MAX_WORD_LENGTH];
    int count;
    int length;
};

struct Word* findWord(struct Word words[], int, const char*);
void wordInfo(FILE*, struct Word*, int*);
void printCompressedFile(FILE*, FILE*, char*, char*);
int findPopularWord(struct Word*, int);
int findRarityWord(struct Word*, int);
void printDollar(FILE*, char*, char*);
int quantityWord(FILE*);
//void allocateText(struct Word*, int, int);






#endif //LAB2SEM2_FUNCTIONS_H
