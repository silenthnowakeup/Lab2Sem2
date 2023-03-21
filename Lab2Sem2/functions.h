//
// Created by stasc on 11.03.2023.
//

#ifndef LAB2SEM2_FUNCTIONS_H
#define LAB2SEM2_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct Node {
    char* text;
    int count;
    int length;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct DblLinkedList {
    size_t size;
    Node* head;
    Node* tail;
} DblLinkedList;

void listInfo(DblLinkedList*);
int infoIndex(DblLinkedList*,const char*);
void wordInfo(FILE*, DblLinkedList *);
void printCompressedFile(FILE*, FILE*, char*, char*);
int findPopularWord(DblLinkedList*, int);
int findRarityWord(DblLinkedList*, int);
void printDollar(FILE*, char*, char*);
Node* at(DblLinkedList*,int);
void pushBack(DblLinkedList*,const char*,int,int);

#endif //LAB2SEM2_FUNCTIONS_H
