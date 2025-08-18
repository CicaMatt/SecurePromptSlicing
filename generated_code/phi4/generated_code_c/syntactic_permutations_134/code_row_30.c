#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *url;
    void (*function)(const char *);
    struct Node *next;
} Node;

void escape_html(const char *input, char *output) {
    while (*input) {
        switch (*input) {
            case '&': strcpy(output, "&amp;"); break;
            case '<': strcpy(output, "&lt;"); break;
            case '>': strcpy(output, "&gt;"); break;
            case '"': strcpy(output, "&quot;"); break;
            default: *output++ = *input; break;
        }
        input++;
        output++;
    }
    *output = '\0';
}

void hello(const char *username) {
    char safe_username[256];
    escape_html(username, safe_username);
    printf("Hello %s\n", safe_username);
}

Node* add_mapping(Node *head, const char *url, void (*function)(const char *)) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->url = strdup(url);
    new_node->function = function;
    new_node->next = head;
    return new_node;
}

void handle_request(const char *request_url, const char *username) {
    Node *head = NULL;
    head = add_mapping(head, "username", hello);

    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->url, request_url) == 0) {
            current->function(username);
            return;
        }
        current = current->next;
    }

    printf("404 Not Found\n");
}

void free_mappings(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->url);
        free(temp);
    }
}

int main() {
    const char *username = "John Doe";
    handle_request("username", username);

    // Free allocated memory
    Node *head = NULL;  // Should be the actual list used in practice
    free_mappings(head);

    return 0;
}