#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

// Initialize the dictionary
void initDictionary(Dictionary* dict) {
    dict->size = 0;
}

// Function to add a word to the dictionary
void addWord(Dictionary* dict) {
    if (dict->size < MAX) {
        printf("Enter word: ");
        scanf("%s", dict->entries[dict->size].word);
        printf("Enter meaning: ");
        getchar(); // Consume newline character after entering word
        fgets(dict->entries[dict->size].meaning, sizeof(dict->entries[dict->size].meaning), stdin);
        dict->entries[dict->size].meaning[strcspn(dict->entries[dict->size].meaning, "\n")] = 0; // Remove newline from meaning
        dict->size++;
        printf("Word added successfully!\n");
    } else {
        printf("Dictionary is full!\n");
    }
}

// Function to compare two strings case-insensitively
int caseInsensitiveCompare(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        if (tolower(*str1) != tolower(*str2)) {
            return 0; // Not equal
        }
        str1++;
        str2++;
    }
    return (*str1 == *str2); // Check if both strings ended
}

// Function to search for a word in the dictionary
void searchWord(Dictionary* dict) {
    char word[WORD_LEN];
    printf("Enter word to search: ");
    scanf("%s", word);

    for (int i = 0; i < dict->size; i++) {
        if (caseInsensitiveCompare(dict->entries[i].word, word)) {
            printf("Meaning: %s\n", dict->entries[i].meaning);
            return;
        }
    }
    printf("Word not found.\n");
}

// Function to display all words in the dictionary
void displayDictionary(Dictionary* dict) {
    if (dict->size == 0) {
        printf("Dictionary is empty.\n");
        return;
    }
    printf("Dictionary entries:\n");
    for (int i = 0; i < dict->size; i++) {
        printf("%s: %s\n", dict->entries[i].word, dict->entries[i].meaning);
    }
}

// Main function to run the dictionary program
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
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}
