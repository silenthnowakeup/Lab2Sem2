//
// Created by stasc on 11.03.2023.
//

#ifndef LAB2SEM2_FUNCTIONS_H
#define LAB2SEM2_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LENGTH_WORD 50




#define MAX_WORD_LENGTH 50


typedef struct _Node {
    char text[MAX_WORD_LENGTH];
    int count;
    int length;
    struct _Node* next;
    struct _Node* prev;
} Node;

typedef struct _DblLinkedList {
    size_t size;
    Node* head;
    Node* tail;
} DblLinkedList;

void listInfo(DblLinkedList*);
int infoBlyad(DblLinkedList*,char*);
void wordInfo(FILE*, DblLinkedList *, int*);
void printCompressedFile(FILE*, FILE*, char*, char*);
int findPopularWord(DblLinkedList*, int);
int findRarityWord(DblLinkedList*, int);
void printDollar(FILE*, char*, char*);
Node* at(DblLinkedList*,int);
void pushBack(DblLinkedList*,char*,int,int);
//void allocateText(struct Word*, int, int);






#endif //LAB2SEM2_FUNCTIONS_H
