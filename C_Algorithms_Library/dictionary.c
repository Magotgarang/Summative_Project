#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define WORD_LEN 30

typedef struct {
    char word[WORD_LEN];
    char meaning[200];
} DictionaryEntry;

typedef struct {
    DictionaryEntry entries[MAX];
    int size;
} Dictionary;

void initDictionary(Dictionary* dict) {
    dict->size = 0;
}

void addWord(Dictionary* dict) {
    if (dict->size < MAX) {
        printf("Enter word: ");
        scanf("%s", dict->entries[dict->size].word);
        printf("Enter meaning: ");
        getchar(); // Consume newline
        fgets(dict->entries[dict->size].meaning, 200, stdin);
        dict->size++;
    } else {
        printf("Dictionary is full!\n");
    }
}

void searchWord(Dictionary* dict) {
    char word[WORD_LEN];
    printf("Enter word to search: ");
    scanf("%s", word);

    for (int i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].word, word) == 0) {
            printf("Meaning: %s", dict->entries[i].meaning);
            return;
        }
    }
    printf("Word not found.\n");
}

void displayDictionary(Dictionary* dict) {
    for (int i = 0; i < dict->size; i++) {
        printf("%s: %s", dict->entries[i].word, dict->entries[i].meaning);
    }
}

int main() {
    Dictionary dict;
    initDictionary(&dict);
    int choice;

    do {
        printf("1. Add Word\n2. Search Word\n3. Display Dictionary\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addWord(&dict);
                break;
            case 2:
                searchWord(&dict);
                break;
            case 3:
                displayDictionary(&dict);
                break;
            case 4:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}

