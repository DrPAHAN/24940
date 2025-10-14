#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *str;
    struct Node *next;
} Node;

void append(Node **head, const char *line) {
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    size_t len = strlen(line);
    new_node->str = malloc(len + 1);
    if (!new_node->str) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->str, line);
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

void free_list(Node *head) {
    while (head) {
        Node *next = head->next;
        free(head->str);
        free(head);
        head = next;
    }
}

int main() {
    Node *head = NULL;
    char *buffer = NULL;
    size_t bufsize = 128;

    buffer = malloc(bufsize);
    if (!buffer) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    printf("Введите строки (начинайте строку с '.' чтобы завершить):\n");

    while (1) {
        if (!fgets(buffer, bufsize, stdin)) {
            break;
        }

        while (strchr(buffer, '\n') == NULL) {
            size_t len = strlen(buffer);
            bufsize *= 2;
            char *tmp = realloc(buffer, bufsize);
            if (!tmp) {
                perror("realloc");
                free(buffer);
                free_list(head);
                exit(EXIT_FAILURE);
            }
            buffer = tmp;

            if (!fgets(buffer + len, bufsize - len, stdin)) {
                break;
            }
        }

        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }

        if (buffer[0] == '.') {
            break;
        }

        append(&head, buffer);
    }

    printf("\nВведенные строки:\n");
    for (Node *curr = head; curr != NULL; curr = curr->next) {
        printf("%s\n", curr->str);
    }

    free(buffer);
    free_list(head);
    return 0;
}

