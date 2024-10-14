// Libraries needed

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Node structure(with priority and complition status)

#define MAX_TASK_LENGTH 100
#define FILENAME "todo_list.txt"

typedef struct Node {
    char task[MAX_TASK_LENGTH];
    int priority; // 1 = High, 2 = Medium, 3 = Low
    int completed; // 0 = Not Completed, 1 = Completed
    struct Node* next;
} Node;

//funtion to create a new node

Node* createNode(char* task, int priority) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    strncpy(newNode->task, task, MAX_TASK_LENGTH - 1);
    newNode->task[MAX_TASK_LENGTH - 1] = '\0';
    newNode->priority = priority;
    newNode->completed = 0;
    newNode->next = NULL;
    return newNode;
}

//funtion to add a new task(Sorted by Priority)

void addTask(Node** head, char* task, int priority) {
    Node* newNode = createNode(task, priority);
    if (*head == NULL || (*head)->priority > priority) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL && temp->next->priority <= priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

//function to Display the TO-DO list(With priority and status)

void displayList(Node* head) {
    Node* temp = head;
    int index = 1;
    const char* priorities[] = {"High", "Medium", "Low"};
    
    if (temp == NULL) {
        printf("To-Do List is empty!\n");
        return;
    }
    
    while (temp != NULL) {
        printf("\n\n\n");
        printf("%d. [%s] %s%s\n", index++, priorities[temp->priority - 1], temp->task, temp->completed ? " (Completed)" : "");
        temp = temp->next;
    }
}

//Function to edit a task

void editTask(Node* head, int position, char* newTask, int newPriority) {
    Node* temp = head;
    for (int i = 1; temp != NULL && i < position; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Invalid position!\n");
        return;
    }
    strncpy(temp->task, newTask, MAX_TASK_LENGTH - 1);
    temp->task[MAX_TASK_LENGTH - 1] = '\0';
    temp->priority = newPriority;
}

//Funtion to mark the task as completed

void markTaskCompleted(Node* head, int position) {
    Node* temp = head;
    for (int i = 1; temp != NULL && i < position; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Invalid position!\n");
        return;
    }
    temp->completed = 1;
}

//Funtion to save the TO-DO list to a file

void saveToFile(Node* head) {
    FILE* file = fopen(FILENAME, "w");
    if (!file) {
        printf("Could not open file for saving.\n");
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        fprintf(file, "%s,%d,%d\n", temp->task, temp->priority, temp->completed);
        temp = temp->next;
    }
    fclose(file);
    printf("To-Do List saved to %s\n", FILENAME);
}

//Funtion to load the TO-DO list from a file

void loadFromFile(Node** head) {
    FILE* file = fopen(FILENAME, "r");
    if (!file) {
        printf("No saved file found.\n");
        return;
    }
    
    char line[MAX_TASK_LENGTH + 10];
    char task[MAX_TASK_LENGTH];
    int priority, completed;
    
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%d,%d", task, &priority, &completed);
        Node* newNode = createNode(task, priority);
        newNode->completed = completed;
        addTask(head, task, priority);
    }
    
    fclose(file);
    printf("To-Do List loaded from %s\n", FILENAME);
}

//function to delete tasks

void deleteTask(Node** head, int position) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }

    Node* temp = *head;

    if (position == 1) {
        *head = temp->next;
        free(temp);
        return;
    }

    for (int i = 1; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Invalid position!\n");
        return;
    }

    Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}


//Main Funtion

int main() {
    Node* head = NULL;
    int choice, position, priority;
    char task[MAX_TASK_LENGTH];

    loadFromFile(&head);

    while (1) {
        printf("\n1. Add Task\n2. Display To-Do List\n3. Edit Task\n4. Mark Task as Completed\n5. Delete Task\n6. Save To-Do List\n7. Load from file\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline left by scanf

        switch (choice) {
            case 1:
                printf("Enter task: ");
                fgets(task, MAX_TASK_LENGTH, stdin);
                task[strcspn(task, "\n")] = '\0';  // Remove newline character
                printf("Enter priority (1 = High, 2 = Medium, 3 = Low): ");
                scanf("%d", &priority);
                addTask(&head, task, priority);
                break;
            case 2:
                displayList(head);
                break;
            case 3:
                printf("Enter task number to edit: ");
                scanf("%d", &position);
                getchar();  // Consume newline left by scanf
                printf("Enter new task description: ");
                fgets(task, MAX_TASK_LENGTH, stdin);
                task[strcspn(task, "\n")] = '\0';
                printf("Enter new priority (1 = High, 2 = Medium, 3 = Low): ");
                scanf("%d", &priority);
                editTask(head, position, task, priority);
                break;
            case 4:
                printf("Enter task number to mark as completed: ");
                scanf("%d", &position);
                markTaskCompleted(head, position);
                break;
            case 5:
                printf("Enter task number to delete: ");
                scanf("%d", &position);
                deleteTask(&head, position);
                break;
            case 6:
                saveToFile(head);
                break;
            case 7:
                loadFromFile(&head);
                break;
            case 8:
                saveToFile(head);
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
