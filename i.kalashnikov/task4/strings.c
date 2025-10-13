#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

typedef struct Node {
    char *str;
    struct Node *next;
} Node;

void add_to_list(Node **head, Node **tail, char *str) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_node->str = str;
    new_node->next = NULL;
    
    if (*head == NULL) {
        *head = new_node;
        *tail = new_node;
    } else {
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

char *read_line() {
    struct termios oldt, newt;
    if (tcgetattr(STDIN_FILENO, &oldt) == -1) {
        perror("tcgetattr");
        exit(1);
    }
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_cc[VMIN] = 1;
    newt.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) == -1) {
        perror("tcsetattr");
        exit(1);
    }

    int capacity = 16;
    char *line = (char *)malloc(capacity);
    if (!line) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    int size = 0;
    int c;

    while (1) {
        c = getchar();
        if (c == EOF || c == '\n') {
            break;
        }
        if (c == 27) {  // ESC
            // Skip escape sequence
            c = getchar();
            if (c == EOF || c == '\n') {
                break;
            }
            if (c == '[') {
                // ANSI sequence, skip until finalizer (@ to ~)
                do {
                    c = getchar();
                    if (c == EOF || c == '\n') {
                        goto end_loop;
                    }
                } while (!(c >= '@' && c <= '~'));
            }
            // Ignore other esc, continue
            continue;
        }
        if (c == 127 || c == 8) {  // Backspace or Ctrl-H
            if (size > 0) {
                size--;
            }
            continue;
        }
        if (isprint((unsigned char)c) || c == '\t') {
            if (size + 1 >= capacity) {
                capacity *= 2;
                char *temp = (char *)realloc(line, capacity);
                if (!temp) {
                    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                    fprintf(stderr, "Memory reallocation failed\n");
                    free(line);
                    exit(1);
                }
                line = temp;
            }
            line[size++] = (char)c;
        }
        // Ignore other characters
    }

end_loop:
    if (tcsetattr(STDIN_FILENO, TCSANOW, &oldt) == -1) {
        perror("tcsetattr restore");
    }

    if (c == EOF && size == 0) {
        free(line);
        return NULL;
    }

    if (size + 1 >= capacity) {
        capacity += 1;
        char *temp = (char *)realloc(line, capacity);
        if (!temp) {
            fprintf(stderr, "Memory reallocation failed\n");
            free(line);
            exit(1);
        }
        line = temp;
    }
    line[size] = '\0';

    return line;
}

int main() {
    Node *head = NULL;
    Node *tail = NULL;
    
    while (1) {
        char *str = read_line();
        if (str == NULL) {
            break; // EOF reached
        }
        
        if (strlen(str) == 0) {
            free(str);
            continue;
        }
        
        if (str[0] == '.') {
            free(str);
            break;
        }
        
        add_to_list(&head, &tail, str);
    }
    
    // Output the list
    Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->str);
        current = current->next;
    }
    
    // Free memory
    current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->str);
        free(temp);
    }
    
    return 0;
}