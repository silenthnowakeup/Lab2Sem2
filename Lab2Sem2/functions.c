//
// Created by stasc on 11.03.2023.
//

#include "functions.h"
#define MAX_WORD_LENGTH 50



//pushback and Node* at(list, pos);

//pushback and Node* at(list, pos);

void pushBack(DblLinkedList* list, char* text, int length, int count)
{
    Node* ptr = (Node*)malloc(1 * sizeof(Node));
    ptr->count = count;
    ptr->length = length;
    strcpy(ptr->text, text);
    if (list->head == NULL) {
        ptr->next = NULL;
        ptr->prev = NULL;
        list->head = ptr;
        list->tail = ptr;
        list->size++;
    }
    else {
        ptr->next = NULL;
        ptr->prev = list->tail;
        list->tail->next = ptr;
        list->tail = ptr;
        list->size++;
    }
}

//Node* at(DblLinkedList* list, int pos) {
//    int i = 0;
//    Node* node = NULL;
//    if (list->size / 2 >= pos) {
//        node = list->head;
//        while (node != NULL && i < pos) {
//            node = node->next;
//            i++;
//        }
//    }
//    else
//    {
//        node = list->tail;
//        while (node != NULL && i < (list->size - pos - 1)) {
//            node = node->prev;
//            i++;
//        }
//    }
//    return node;
//}

Node* at(DblLinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        return NULL;
    }
    if (index == list->size - 1)
    {
        return list->tail;
    }
    Node* current = list->head;

    for (size_t i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current;
}

void listInfo(DblLinkedList* list)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp = list->head;
    while (temp != NULL)
    {
        printf("%d %d %s\n", temp->count, temp->length, temp->text);
        temp = temp->next;
    }
}

int infoBlyad(DblLinkedList* list, char* cmp_word)
{
    if (list->head != NULL)
    {
        Node* ptr = (Node*)malloc(sizeof(Node));
        ptr = list->head;
        int i = 0;
        while (ptr != NULL)
        {
            if (strcmp(ptr->text, cmp_word) == 0)
            {
                return i;
            }
            ptr = ptr->next;
            i++;
        }
        return -1;
    }
    else
        return -1;
}


void wordInfo(FILE* file, DblLinkedList* list, int* wordsCount) {
    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) == 1) {
        int len = strlen(word);
        if (len > 0 && ispunct(word[len - 1])) {
            // Удаляем знак препинания из конца слова
            char temp[MAX_WORD_LENGTH];
            strncpy(temp, word, len - 1);
            temp[len - 1] = '\0';
            strcpy(word, temp);
        }
        int index = 0;
        if ((index =infoBlyad(list, word)) == -1) {
            // Слово встретилось впервые - добавляем его в массив
            pushBack(list, word, strlen(word), 1);
            //            words[*wordsCount].count = 1;
            //            words[*wordsCount].length = strlen(word);
        }
        else {
            at(list, index)->count++;
            // Слово уже было в массиве - увеличиваем его счетчик

        }
    }
}

void printCompressedFile(FILE* file, FILE* compressedFile, char* wordA, char* wordB) {
    char word[MAX_WORD_LENGTH];
    printf("\nWordA::%s, WordB::%s", wordA, wordB);

    while (fscanf(file, "%s", word) == 1) {
        int len = strlen(word);
        if (ispunct(word[len - 1])) {
            char lastChar = word[len - 1];
            word[len - 1] = '\0';
            if (strcmp(word, wordA) == 0) {
                fprintf(compressedFile, "%s%c ", wordB, lastChar);
            }
            else if (strcmp(word, wordB) == 0) {
                fprintf(compressedFile, "%s%c ", wordA, lastChar);
            }
            else {
                fprintf(compressedFile, "%s%c ", word, lastChar);
            }
        }
        else {
            if (strcmp(word, wordA) == 0) {
                fprintf(compressedFile, "%s ", wordB);
            }
            else if (strcmp(word, wordB) == 0) {
                fprintf(compressedFile, "%s ", wordA);
            }
            else {
                fprintf(compressedFile, "%s ", word);
            }
        }
    }
}


int findPopularWord(DblLinkedList* list, int wordsCount)
{
    int most_popular_index = -1;
    int max_length_count = -1;
    for (int i = 0; i < wordsCount; i++)
    {
        if (at(list, i)->length > 4)
        {
            int lengthCount = at(list, i)->length * at(list, i)->count;
            if (lengthCount > max_length_count) {
                max_length_count = lengthCount;
                most_popular_index = i;
            }
        }
    }
    return most_popular_index;
}

int findRarityWord(DblLinkedList* list, int wordsCount) {
    int most_rarity_index = -1;
    int min_length_count = INT_MAX;
    for (int i = 0; i < wordsCount; i++) {
        if (at(list, i)->length <= 4 && at(list, i)->length > 0) {
            int lengthCount = at(list, i)->length * at(list, i)->count;
            if (lengthCount < min_length_count) {
                min_length_count = lengthCount;
                most_rarity_index = i;
            }
        }
    }
    return most_rarity_index;
}

void printDollar(FILE* compressFile, char* wordA, char* wordB)
{
    fseek(compressFile, 0, SEEK_END);
    fprintf(compressFile, "$%s $%s", wordA, wordB);
}

int quantityWord(FILE* file)
{
    int count = 0;
    char c;
    while ((c = getc(file)) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            count++;
        }
    }
    printf("%d\n", count);
    return count;
}
