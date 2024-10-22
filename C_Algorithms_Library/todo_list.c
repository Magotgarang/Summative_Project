#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define TASK_LEN 100

typedef struct {
    char task[TASK_LEN];
    int completed;
} Todo;

typedef struct {
    Todo tasks[MAX];
    int size;
} TodoList;

void initList(TodoList* list) {
    list->size = 0;
}

void addTask(TodoList* list) {
    if (list->size < MAX) {
        printf("Enter task: ");
        getchar(); // Consume newline
        fgets(list->tasks[list->size].task, TASK_LEN, stdin);
        list->tasks[list->size].completed = 0;
        list->size++;
    } else {
        printf("Todo list is full!\n");
    }
}

void completeTask(TodoList* list) {
    int index;
    printf("Enter task number to complete (0 to %d): ", list->size - 1);
    scanf("%d", &index);
    if (index >= 0 && index < list->size) {
        list->tasks[index].completed = 1;
        printf("Task %d marked as completed.\n", index);
    } else {
        printf("Invalid task number.\n");
    }
}

void displayTasks(TodoList* list) {
    for (int i = 0; i < list->size; i++) {
        printf("%d. [%s] %s", i, list->tasks[i].completed ? "x" : " ", list->tasks[i].task);
    }
}

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
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}

