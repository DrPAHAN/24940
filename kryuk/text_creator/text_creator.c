#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for linked list node
struct Node {
    char *data;         
    struct Node *next;  
};

int add_string(struct Node **head, struct Node **current) {
    printf("> ");
        
    char *input = NULL;       // Dynamic buffer for input
    size_t input_size = 0;    // Size of allocated buffer

    // Read input
    ssize_t bytes_read = getline(&input, &input_size, stdin);
    
    if (bytes_read <= 0) {
        printf("Error reading input\n");
        return 1;
    }
    
    if (input[0] == '.') {
        return 1;
    }
    
    // Allocate memory
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    if (input[bytes_read-1] == '\n') {
        input[bytes_read-1] = '\0';
        bytes_read -= 1;
    }
    
    newNode->data = (char*)malloc(bytes_read + 1);
    if (newNode->data == NULL) {
        printf("Memory allocation failed\n");
        free(newNode);
        return 1;
    }
    
    // Copy string to allocated memory
    strcpy(newNode->data, input);
    newNode->next = NULL;
    
    // Add node to list
    if (head == NULL) {
        head = newNode;
        current = newNode;
    } else {
        current->next = newNode;
        current = newNode;
    }

    // Free input buffer
    if (input != NULL) {
        free(input);
    }

    return 0;
}

int main() {
    struct Node *head = NULL;  // Head of the linked list
    struct Node *current = NULL;  // Current node pointer
    
    printf("Enter strings:\n");
    
    while (1) {
        if (add_string(&head, &current)) {
            break;
        }
    }
    
    printf("\nAll entered strings:\n");
    current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
    
    return 0;
}

