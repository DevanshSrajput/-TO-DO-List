#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Task structure
typedef struct Task {
    int id;                     // Unique identifier for the task
    char description[100];      // Description of the task
    char dueDate[11];           // Due date of the task (YYYY-MM-DD)
    int completed;              // Completion status (0 for not completed, 1 for completed)
} Task;

// Define the TreeNode structure
typedef struct TreeNode {
    Task task;                 // Task associated with this node
    struct TreeNode* left;     // Pointer to left child
    struct TreeNode* right;    // Pointer to right child
} TreeNode;

// Function to create a new task
Task createTask(int id, const char* description, const char* dueDate) {
    Task newTask;
    newTask.id = id;
    strcpy(newTask.description, description);
    strcpy(newTask.dueDate, dueDate);
    newTask.completed = 0; // Initially not completed
    return newTask;
}

// Function to create a new tree node
TreeNode* createNode(Task task) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->task = task;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a task into the tree
TreeNode* insert(TreeNode* root, Task task) {
    if (root == NULL) {
        return createNode(task);
    }
    
    if (task.id < root->task.id) {
        root->left = insert(root->left, task);
    } else {
        root->right = insert(root->right, task);
    }
    
    return root;
}

// Function to display tasks in-order
void displayTasks(TreeNode* root) {
    if (root != NULL) {
        displayTasks(root->left);
        printf("ID: %d, Description: %s, Due Date: %s, Completed: %d\n",
               root->task.id, root->task.description,
               root->task.dueDate, root->task.completed);
        displayTasks(root->right);
    }
}

// Function to mark a task as completed
void completeTask(TreeNode* root, int id) {
    if (root == NULL) return;

    if (id < root->task.id) {
        completeTask(root->left, id);
    } else if (id > root->task.id) {
        completeTask(root->right, id);
    } else {
        root->task.completed = 1; // Mark as completed
        printf("Task ID %d marked as completed.\n", id);
    }
}

// Function to modify a task's details
void modifyTask(TreeNode* root, int id, const char* newDescription, const char* newDueDate) {
    if (root == NULL) {
        printf("Task ID %d not found.\n", id);
        return;
    }

    if (id < root->task.id) {
        modifyTask(root->left, id, newDescription, newDueDate);
    } else if (id > root->task.id) {
        modifyTask(root->right, id, newDescription, newDueDate);
    } else {
        // Task found; modify it
        strcpy(root->task.description, newDescription);
        strcpy(root->task.dueDate, newDueDate);
        printf("Task ID %d modified successfully.\n", id);
   }
}

// Function to delete a task from the tree
TreeNode* deleteTask(TreeNode* root, int id) {
   if (root == NULL) {
       printf("Task ID %d not found.\n", id);
       return root;
   }

   if (id < root->task.id) {
       root->left = deleteTask(root->left, id);
   } else if (id > root->task.id) {
       root->right = deleteTask(root->right, id);
   } else { 
       // Node with only one child or no child 
       if (root->left == NULL) { 
           TreeNode *temp = root -> right; 
           free(root); 
           return temp; 
       } else if (root -> right == NULL) { 
           TreeNode *temp = root -> left; 
           free(root); 
           return temp; 
       }

       // Node with two children: Get the inorder successor 
       TreeNode *temp = root -> right; 
       while (temp && temp -> left != NULL) { 
           temp = temp -> left; 
       }

       // Copy the inorder successor's content to this node 
       root -> task = temp -> task;

       // Delete the inorder successor 
       root -> right = deleteTask(root -> right , temp -> task.id); 
   }
   return root; 
}

// Function to get user input for a new task
void getUserInput(Task *newTask) {
    printf("Enter Task ID: ");
    scanf("%d", &newTask->id);
    
    printf("Enter Task Description: ");
    getchar();  // Consume newline character left by scanf
    fgets(newTask->description, sizeof(newTask->description), stdin);
    
    // Remove newline character from description if present
    size_t len = strlen(newTask->description);
    if (len > 0 && newTask->description[len - 1] == '\n') {
        newTask->description[len - 1] = '\0';
    }

    printf("Enter Due Date (YYYY-MM-DD): ");
    fgets(newTask->dueDate, sizeof(newTask->dueDate), stdin);

    // Remove newline character from due date if present
    len = strlen(newTask->dueDate);
    if (len > 0 && newTask->dueDate[len - 1] == '\n') {
        newTask->dueDate[len - 1] = '\0';
    }

    newTask->completed = 0; // Initially not completed
}

// Main function to demonstrate usage
int main() {
   TreeNode* todoList = NULL;
   int choice;

   do {
       printf("\nTO-DO List Menu:\n");
       printf("1. Add Task\n");
       printf("2. Display Tasks\n");
       printf("3. Modify Task\n");
       printf("4. Delete Task\n");
       printf("5. Complete Task\n");
       printf("6. Exit\n");
       printf("Enter your choice: ");
       scanf("%d", &choice);

       switch(choice) {
           case 1: { // Add Task
               Task newTask;
               getUserInput(&newTask);
               todoList = insert(todoList, newTask);
               break;
           }
           case 2: { // Display Tasks
               printf("\nCurrent TO-DO List:\n");
               displayTasks(todoList);
               break;
           }
           case 3: { // Modify Task
               int id;
               char newDescription[100];
               char newDueDate[11];

               printf("Enter Task ID to modify: ");
               scanf("%d", &id);

               printf("Enter New Description: ");
               getchar();  // Consume newline character left by scanf
               fgets(newDescription, sizeof(newDescription), stdin);

               size_t len = strlen(newDescription);
               if (len > 0 && newDescription[len - 1] == '\n') {
                   newDescription[len - 1] = '\0';
               }

               printf("Enter New Due Date (YYYY-MM-DD): ");
               fgets(newDueDate, sizeof(newDueDate), stdin);

               len = strlen(newDueDate);
               if (len > 0 && newDueDate[len - 1] == '\n') {
                   newDueDate[len - 1] = '\0';
               }

               modifyTask(todoList, id, newDescription, newDueDate);
               break;
           }
           case 4: { // Delete Task
               int id;
               printf("Enter Task ID to delete: ");
               scanf("%d", &id);
               todoList = deleteTask(todoList, id);
               break;
           }
           case 5: { // Complete Task
               int id;
               printf("Enter Task ID to mark as completed: ");
               scanf("%d", &id);
               completeTask(todoList, id);
               break;
           }
           case 6: { // Exit
               printf("Exiting...\n");
               break;
           }
           default:
               printf("Invalid choice! Please try again.\n");
       }
   } while(choice != 6);

   // Free allocated memory (not implemented here for simplicity)

   return 0;
}