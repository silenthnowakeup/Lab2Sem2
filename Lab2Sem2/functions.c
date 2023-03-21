//
// Created by stasc on 11.03.2023.
//

#include "functions.h"

void pushBack(DblLinkedList* list,const char* text, int length, int count)
{
    Node* ptr = (Node*)malloc(1 * sizeof(Node));
    ptr->count = count;
    ptr->length = length;
    if (length > 0) {
    ptr->text = (char*)malloc((ptr->length+1) * sizeof(char));
    strcpy(ptr->text, text);
    } else {
    ptr->text = NULL;
    }
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
    Node* temp;
    temp = list->head;
    while (temp != NULL)
    {
        printf("%d %d %s\n", temp->count, temp->length, temp->text);
        temp = temp->next;
    }
}

int infoBlyad(DblLinkedList* list,const char* cmp_word)
{
    if (list != NULL && list->head != NULL)
    {
        Node* ptr;
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


void wordInfo(FILE* file, DblLinkedList* list) {

    int size = 16;

    char* word = (char*)calloc (size, sizeof(char));
    char* temp = (char*)calloc(size,sizeof(char));

    while (fscanf(file, "%s", word) == 1) {
        const unsigned long len = strlen(word);

        if (len > 0 && ispunct(word[len - 1])) {
            //делит знак препинания из конца слова
            strncpy(temp, word, len - 1);
            temp[len - 1] = '\0';
            strcpy(word, temp);
        }
        int index;
        if ((index = infoBlyad(list, word)) == -1) {
            // если слово встретилось впервые добавляю его
            pushBack(list, word, (int)strlen(word), 1);
        }
        else {
            at(list, index)->count++;
        }
    }
    free(word);
    free(temp);
}

void printCompressedFile(FILE* file, FILE* compressedFile, char* wordA, char* wordB) {
    int size = 16;
    char* word = (char*)calloc(size,sizeof(char));
    printf("\nWordA::%s, WordB::%s", wordA, wordB);

    while (fscanf(file, "%s", word) == 1) {
       unsigned long len = strlen(word);

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
        free(word);
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
    int min_length_count = 100;
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

