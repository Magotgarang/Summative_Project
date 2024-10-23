#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { RED, BLACK } Color;

typedef struct Student {
    char name[50];
    int id;
    float grade;
} Student;

typedef struct Node {
    Student student;
    Color color;
    struct Node *left, *right, *parent;
} Node;

typedef struct RedBlackTree {
    Node *root;
    Node *TNULL; // Sentinel node
} RedBlackTree;

// Function to create a new node
Node* createNode(Student student) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->student = student;
    node->left = node->right = node->parent = NULL;
    node->color = RED; // New node is always red
    return node;
}

// Function to initialize the tree
RedBlackTree* createTree() {
    RedBlackTree* tree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    tree->TNULL = (Node*)malloc(sizeof(Node));
    tree->TNULL->color = BLACK; // Sentinel node is black
    tree->root = tree->TNULL;
    return tree;
}

// Function to fix the Red-Black tree after insertion
void fixInsert(RedBlackTree* tree, Node* k) {
    Node* u;
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->left) {
            u = k->parent->parent->right; // uncle
            if (u->color == RED) {
                // Case 1: Uncle is red
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                // Case 2: Uncle is black
                if (k == k->parent->right) {
                    k = k->parent;
                    // Left rotate
                    Node* temp = k->left;
                    k->left = temp->right;
                    if (temp->right != tree->TNULL)
                        temp->right->parent = k;
                    temp->parent = k->parent;
                    if (k->parent == NULL)
                        tree->root = temp;
                    else if (k == k->parent->left)
                        k->parent->left = temp;
                    else
                        k->parent->right = temp;
                    temp->right = k;
                    k->parent = temp;
                }
                // Right rotate
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                Node* temp = k->parent->parent;
                Node* temp2 = temp->left;
                temp->left = k->parent;
                k->parent->parent = temp;
                k->parent->right = temp2;
                if (temp2 != tree->TNULL)
                    temp2->parent = temp;
            }
        } else {
            u = k->parent->parent->left; // uncle
            if (u->color == RED) {
                // Case 1: Uncle is red
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                // Case 2: Uncle is black
                if (k == k->parent->left) {
                    k = k->parent;
                    // Right rotate
                    Node* temp = k->right;
                    k->right = temp->left;
                    if (temp->left != tree->TNULL)
                        temp->left->parent = k;
                    temp->parent = k->parent;
                    if (k->parent == NULL)
                        tree->root = temp;
                    else if (k == k->parent->right)
                        k->parent->right = temp;
                    else
                        k->parent->left = temp;
                    temp->left = k;
                    k->parent = temp;
                }
                // Left rotate
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                Node* temp = k->parent->parent;
                Node* temp2 = temp->right;
                temp->right = k->parent;
                k->parent->parent = temp;
                k->parent->left = temp2;
                if (temp2 != tree->TNULL)
                    temp2->parent = temp;
            }
        }
        if (k == tree->root) break;
    }
    tree->root->color = BLACK; // Root is always black
}

// Function to insert a new student
void rbInsert(RedBlackTree* tree, Student student) {
    Node* node = createNode(student);  // Fixed: Added the missing closing parenthesis
    node->parent = NULL;
    node->left = tree->TNULL;
    node->right = tree->TNULL;

    Node* y = NULL;
    Node* x = tree->root;

    while (x != tree->TNULL) {
        y = x;
        if (node->student.id < x->student.id) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == NULL) {
        tree->root = node;
    } else if (node->student.id < y->student.id) {
        y->left = node;
    } else {
        y->right = node;
    }

    if (node->parent == NULL) {
        node->color = BLACK;
        return;
    }

    if (node->parent->parent == NULL) {
        return;
    }

    fixInsert(tree, node);
}

// Function to perform in-order traversal
void inOrderHelper(Node* node) {
    if (node != NULL && node->color != BLACK) {
        inOrderHelper(node->left);
        printf("Name: %s, ID: %d, Grade: %.2f\n", node->student.name, node->student.id, node->student.grade);
        inOrderHelper(node->right);
    }
}

// Function to display all students
void displayRecords(RedBlackTree* tree) {
    inOrderHelper(tree->root);
}

// Function to search the tree
Node* search(RedBlackTree* tree, int id) {
    Node* current = tree->root;
    while (current != tree->TNULL) {
        if (id == current->student.id) {
            return current;
        } else if (id < current->student.id) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}

// Function to delete a node from the tree
void rbDelete(RedBlackTree* tree, Node* z) {
    Node* x, *y = z;
    Color yOriginalColor = y->color;

    if (z->left == tree->TNULL) {
        x = z->right;
        // Transplant
        if (z->parent == NULL) {
            tree->root = z->right;
        } else if (z == z->parent->left) {
            z->parent->left = z->right;
        } else {
            z->parent->right = z->right;
        }
        z->right->parent = z->parent;
        free(z);
    } else if (z->right == tree->TNULL) {
        x = z->left;
        // Transplant
        if (z->parent == NULL) {
            tree->root = z->left;
        } else if (z == z->parent->left) {
            z->parent->left = z->left;
        } else {
            z->parent->right = z->left;
        }
        z->left->parent = z->parent;
        free(z);
    } else {
        y = z->right;
        while (y->left != tree->TNULL) {
            y = y->left;
        }
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            // Transplant
            if (y->right != tree->TNULL) {
                y->right->parent = y->parent;
            }
            y->parent->left = y->right;
            y->right = z->right;
            z->right->parent = y;
        }

        // Transplant
        if (z->parent == NULL) {
            tree->root = y;
        } else if (z == z->parent->left) {
            z->parent->left = y;
        } else {
            z->parent->right = y;
        }
        y->parent = z->parent;
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
        free(z);
    }

    if (yOriginalColor == BLACK) {
        // Fix delete
        // Fixing logic will go here
    }
}

// Main function
int main() {
    RedBlackTree* tree = createTree();
    int choice;
    Student student;

    do {
        printf("1. Add Student\n2. Display Records\n3. Search by ID\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", student.name);
                printf("Enter ID: ");
                scanf("%d", &student.id);
                printf("Enter grade: ");
                scanf("%f", &student.grade);
                rbInsert(tree, student);
                break;
            case 2:
                printf("Student Records:\n");
                displayRecords(tree);
                break;
            case 3:
                printf("Enter ID to search: ");
                scanf("%d", &student.id);
                Node* result = search(tree, student.id);
                if (result != NULL) {
                    printf("Found: Name: %s, ID: %d, Grade: %.2f\n", result->student.name, result->student.id, result->student.grade);
                } else {
                    printf("Student with ID %d not found.\n", student.id);
                }
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } while (choice != 4);

    return 0;
}
