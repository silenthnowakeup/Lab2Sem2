//
// Created by stasc on 11.03.2023.
//

#include "functions.h"
#define MAX_WORD_LENGTH 50


// Функция для поиска слова в массиве структур
struct Word* findWord(struct Word words[], int wordsCount, const char* file) {
    for (int i = 0; i < wordsCount; i++) {
        if (strcmp(words[i].text, file) == 0) {
            return &words[i];
        }
    }
    return NULL;
}

void wordInfo(FILE* file, struct Word* words, int* wordsCount) {
    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) == 1) {
        int len = strlen(word);
        if (len > 0 && ispunct(word[len-1])) {
            // Удаляем знак препинания из конца слова
            char temp[MAX_WORD_LENGTH];
            strncpy(temp, word, len-1);
            temp[len-1] = '\0';
            strcpy(word, temp);
        }
        struct Word* wordInfo = findWord(words, *wordsCount, word);
        if (wordInfo == NULL) {
            // Слово встретилось впервые - добавляем его в массив
            strcpy(words[*wordsCount].text, word);
            words[*wordsCount].count = 1;
            words[*wordsCount].length = strlen(word);
            (*wordsCount)++;
        } else {
            // Слово уже было в массиве - увеличиваем его счетчик
            wordInfo->count++;
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
            } else if (strcmp(word, wordB) == 0) {
                fprintf(compressedFile, "%s%c ", wordA, lastChar);
            } else {
                fprintf(compressedFile, "%s%c ", word, lastChar);
            }
        } else {
            if (strcmp(word, wordA) == 0) {
                fprintf(compressedFile, "%s ", wordB);
            } else if (strcmp(word, wordB) == 0) {
                fprintf(compressedFile, "%s ", wordA);
            } else {
                fprintf(compressedFile, "%s ", word);
            }
        }
    }
}


int findPopularWord(struct Word* words, int wordsCount)
{
    int most_popular_index = -1;
    int max_length_count = -1;
    for (int i=0;i<wordsCount;i++)
    {
        if (words[i].length>4)
        {
            int lengthCount = words[i].length * words[i].count;
            if (lengthCount > max_length_count) {
                max_length_count = lengthCount;
                most_popular_index = i;
            }
        }
    }
    return most_popular_index;
}

int findRarityWord(struct Word* words, int wordsCount) {
    int most_rarity_index = -1;
    int min_length_count = INT_MAX;
    for (int i = 0; i < wordsCount; i++) {
        if (words[i].length <= 4 && words[i].length>0) {
            int lengthCount = words[i].length * words[i].count;
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
    fprintf(compressFile,"$%s $%s", wordA,wordB);
}

int quantityWord(FILE* file)
{
    int count = 1;
    char c;
    while ((c = getc(file)) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            count++;
        }
    }
    printf("%d\n",count);
    return count;
}

int maxWordLength(FILE* file, struct Word* words, int countWords)
{
    int maxLength = 0;
    int currentLength;
    for (int i = 0; i < countWords; i++)
    {
        currentLength = words[i].length;
        printf("%d\n", currentLength);
        if (currentLength > maxLength)
            maxLength = currentLength;
    }
    printf("%d\n",maxLength);
    return maxLength;
}

/*void allocateText(struct Word* words, int countWords, int maxLength) {
    for (int i = 0; i < countWords; i++) {
        words[i].text = (char*)malloc((maxLength + 1) * sizeof(char));
    }
}*/
