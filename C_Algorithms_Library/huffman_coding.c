#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

typedef struct Node {
    char data;
    unsigned freq;
    struct Node *left, *right;
} Node;

Node* createNode(char data, unsigned freq) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->left = newNode->right = NULL;
    newNode->data = data;
    newNode->freq = freq;
    return newNode;
}

void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform heapify
void minHeapify(Node* arr[], int n, int i) {
    int smallest = i, left = 2 * i + 1, right = 2 * i + 2;

    if (left < n && arr[left]->freq < arr[smallest]->freq)
        smallest = left;
    if (right < n && arr[right]->freq < arr[smallest]->freq)
        smallest = right;

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

// Function to build the Huffman tree
Node* buildHuffmanTree(char data[], int freq[], int size) {
    Node* arr[MAX];
    for (int i = 0; i < size; i++)
        arr[i] = createNode(data[i], freq[i]);

    int n = size;
    while (n > 1) {
        minHeapify(arr, n, 0);
        Node* left = arr[0];
        arr[0] = arr[n - 1];
        n--;
        minHeapify(arr, n, 0);
        Node* right = arr[0];

        Node* newNode = createNode('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        arr[n] = newNode;
        n++;
    }
    return arr[0];
}

// Function to print the Huffman codes
void printCodes(Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!root->left && !root->right) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; i++)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// Function to compress a file
void compressFile(const char* inputFile, const char* outputFile) {
    FILE *in = fopen(inputFile, "r");
    if (in == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int freq[MAX] = {0};
    char data[MAX];
    int size = 0;

    char ch;
    while ((ch = fgetc(in)) != EOF) {
        freq[(unsigned char)ch]++;
    }
    fclose(in);

    for (int i = 0; i < MAX; i++) {
        if (freq[i] > 0) {
            data[size] = (char)i;
            size++;
        }
    }

    Node* root = buildHuffmanTree(data, freq, size);
    int arr[MAX], top = 0;

    printf("Huffman Codes:\n");
    printCodes(root, arr, top);
}

// Main function
int main() {
    char inputFile[100], outputFile[100];
    printf("Enter the input file name: ");
    scanf("%s", inputFile);
    printf("Enter the output file name: ");
    scanf("%s", outputFile);

    compressFile(inputFile, outputFile);
    return 0;
}

