#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node {
    char data;
    int frequency;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(char data, int frequency) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* huffBuild(char* input) {
    int frequencies[256] = {0};

    // Calculate the frequency of each character in the input string
    for (int i = 0; input[i] != '\0'; i++) {
        char currentChar = input[i];
        int ascii = (int)currentChar;
        frequencies[ascii]++;
    }

    struct Node* nodes[256];
    int nodecount = 0;

    // Create nodes for each character with non-zero frequency
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            nodes[nodecount++] = newNode((char)i, frequencies[i]);
        }
    }

    // Build the Huffman tree
    while (nodecount > 1) {
        // Find min0 and min1
        int min0 = 0, min1 = 1;
        for (int i = 2; i < nodecount; i++) {
            if (nodes[i]->frequency < nodes[min0]->frequency) {
                min1 = min0;
                min0 = i;
            } else if (nodes[i]->frequency < nodes[min1]->frequency) {
                min1 = i;
            }
        }

        // Merge the two lowest frequency nodes into a new internal node
        struct Node* internal = newNode('#', nodes[min0]->frequency + nodes[min1]->frequency);
        internal->left = nodes[min0];
        internal->right = nodes[min1];

        nodes[min0] = internal;
        nodes[min1] = nodes[--nodecount];
    }

    return nodes[0];//remaining last node is root
}

void printcodes(struct Node* root, char code[], int top) {
    if (root->left != NULL) {
        code[top] = '0';
        printcodes(root->left, code, top + 1);
    }
    if (root->right != NULL) {
        code[top] = '1';
        printcodes(root->right, code, top + 1);
    }
    if (root->left == NULL && root->right == NULL) {
        code[top] = '\0';
        printf("Character: %c, Code: %s\n", root->data, code);

    }
}

void printHuffmanCodes(struct Node* root) {
    char code[256];
    printcodes(root, code, 0);
}

int main() {
    char input[100];
    printf("Enter required string to encode: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove new line

    struct Node* huffmanroot = huffBuild(input);
    printf("\nHuffman Codes:\n");
    printHuffmanCodes(huffmanroot);

    return 0;
}

