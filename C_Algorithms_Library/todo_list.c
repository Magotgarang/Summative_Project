#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TASK_LEN 100

typedef struct Task {
    int id; // Unique identifier for the task
    char description[TASK_LEN];
    int completed;
    struct Task* next; // Pointer to the next task
} Task;

typedef struct {
    Task* head; // Head pointer for the linked list
    int size;   // Number of tasks in the list
} TodoList;

// Function to initialize the TodoList
void initList(TodoList* list) {
    list->head = NULL;
    list->size = 0;
}

// Function to create a new task
Task* createTask(int id, const char* description) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    if (newTask == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newTask->id = id;
    strncpy(newTask->description, description, TASK_LEN);
    newTask->completed = 0;
    newTask->next = NULL;
    return newTask;
}

// Function to add a task to the list
void addTask(TodoList* list) {
    char description[TASK_LEN];
    printf("Enter task description: ");
    getchar(); // Consume newline
    fgets(description, TASK_LEN, stdin);
    description[strcspn(description, "\n")] = 0; // Remove the newline character

    Task* newTask = createTask(list->size + 1, description);
    newTask->next = list->head; // Insert at the beginning
    list->head = newTask;
    list->size++;
    printf("Task added successfully!\n");
}

// Function to complete a task by ID and remove it from the list
void completeTask(TodoList* list) {
    int id;
    printf("Enter task ID to complete: ");
    scanf("%d", &id);

    Task** current = &list->head; // Use a pointer to pointer to remove the task
    while (*current != NULL) {
        if ((*current)->id == id) {
            Task* temp = *current;
            *current = (*current)->next; // Remove task from the list
            free(temp); // Free the memory of the removed task
            list->size--;
            printf("Task %d marked as completed and removed from the list.\n", id);
            return;
        }
        current = &(*current)->next;
    }
    printf("Task with ID %d not found.\n", id);
}

// Function to display all tasks in the list
void displayTasks(TodoList* list) {
    if (list->size == 0) {
        printf("No tasks available.\n");
        return;
    }
    Task* current = list->head;
    printf("Tasks:\n");
    while (current != NULL) {
        printf("%d. [%s] %s\n", current->id, current->completed ? "x" : " ", current->description);
        current = current->next;
    }
}

// Main function to run the to-do list manager
int main() {
    TodoList list;
    initList(&list);
    int choice;

    do {
        printf("1. Add Task\n2. Complete Task\n3. Display Tasks\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addTask(&list);
                break;
            case 2:
                completeTask(&list);
                break;
            case 3:
                displayTasks(&list);
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
