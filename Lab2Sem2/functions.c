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

int checkVigoda(DblLinkedList* list, int pop, int rare) {
    int lenA = at(list, pop)->length;
    int lenB = at(list, rare)->length;
    int countA = at(list, pop)->count;
    int countB = at(list, rare)->count;

    if ((lenA * countA)/10 > lenB * countB ) {
        return 1;
    } else {
        return 0;
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

int infoIndex(DblLinkedList* list,const char* cmp_word)
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

    int size = 32;

    char* word = (char*)calloc (size, sizeof(char));
    char* temp = (char*)calloc(size,sizeof(char));

    while (fscanf(file, "%32s", word) == 1) {
        const unsigned long len = strlen(word);

        if (len > 0 && ispunct(word[len - 1])) {
            //делит знак препинания из конца слова
            strncpy(temp, word, len - 1);
            temp[len - 1] = '\0';
            strcpy(word, temp);
        }
        int index;
        if ((index = infoIndex(list, word)) == -1) {
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

void printCompressedFile(FILE* file,FILE* compressedFile, char** wordsA, char** wordsB, int numReplacements) {
    int size = 16;
    char* word = (char*)calloc(size,sizeof(char));

    while (fscanf(file, "%16s", word) == 1) {
        unsigned long len = strlen(word);

        if (ispunct(word[len - 1])) {
            char lastChar = word[len - 1];
            word[len - 1] = '\0';
            int found = 0;
            for (int i = 0; i < numReplacements; i++) {
                if (strcmp(word, wordsA[i]) == 0) {
                    fprintf(compressedFile, "%s%c ", wordsB[i], lastChar);
                    found = 1;
                    break;
                }
                else if (strcmp(word, wordsB[i]) == 0) {
                    fprintf(compressedFile, "%s%c ", wordsA[i], lastChar);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                fprintf(compressedFile, "%s%c ", word, lastChar);
            }
        }
        else {
            int found = 0;
            for (int i = 0; i < numReplacements; i++) {
                if (strcmp(word, wordsA[i]) == 0) {
                    fprintf(compressedFile, "%s ", wordsB[i]);
                    found = 1;
                    break;
                }
                else if (strcmp(word, wordsB[i]) == 0) {
                    fprintf(compressedFile, "%s ", wordsA[i]);
                    found = 1;
                    break;
                }
            }
            if (!found) {
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
        if(at(list,i)->length >=4) {
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
        if(at(list,i)->length<4) {
            int lengthCount = at(list, i)->length * at(list, i)->count;
            if (lengthCount < min_length_count) {
                min_length_count = lengthCount;
                most_rarity_index = i;
            }
        }
        }
    return most_rarity_index;
}


void removeNode(DblLinkedList*list,const char *wordRemove) {
    Node* nodeRemove = list->head;

    while (nodeRemove != NULL) {
        if (strcmp(nodeRemove->text, wordRemove) == 0) {
            if (nodeRemove == list->head) {
                list->head = nodeRemove->next;
                if (list->head != NULL) {
                    list->head->prev = NULL;
                }
            } else if (nodeRemove == list->tail) {
                list->tail = nodeRemove->prev;
                if (list->tail != NULL) {
                    list->tail->next = NULL;
                }
            } else {
                nodeRemove->prev->next = nodeRemove->next;
                nodeRemove->next->prev = nodeRemove->prev;
            }
            free(nodeRemove);
            list->size--;
            return;
        }
        nodeRemove = nodeRemove->next;
    }
}

void printDollar(FILE* compressFile, char** wordA, char** wordB,int num)
{
    for(int i = 0;i<num;i++) {
        fprintf(compressFile, "$%s$%s", wordA[i], wordB[i]);
    }
    fprintf(compressFile,"\n");
}
