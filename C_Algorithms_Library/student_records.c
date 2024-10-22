#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
    int id;
    float grade;
} Student;

typedef struct {
    Student students[MAX];
    int size;
} StudentRecords;

void initRecords(StudentRecords* records) {
    records->size = 0;
}

void addStudent(StudentRecords* records) {
    if (records->size < MAX) {
        printf("Enter student name: ");
        scanf("%s", records->students[records->size].name);
        printf("Enter student ID: ");
        scanf("%d", &records->students[records->size].id);
        printf("Enter student grade: ");
        scanf("%f", &records->students[records->size].grade);
        records->size++;
    } else {
        printf("Records are full!\n");
    }
}

void displayRecords(StudentRecords* records) {
    for (int i = 0; i < records->size; i++) {
        printf("Name: %s, ID: %d, Grade: %.2f\n", records->students[i].name, records->students[i].id, records->students[i].grade);
    }
}

int main() {
    StudentRecords records;
    initRecords(&records);
    int choice;

    do {
        printf("1. Add Student\n2. Display Records\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addStudent(&records);
                break;
            case 2:
                displayRecords(&records);
                break;
            case 3:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 3);

    return 0;
}

