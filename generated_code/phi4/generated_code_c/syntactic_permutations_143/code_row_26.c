#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char *email;
} Subscriber;

typedef struct Node {
    Subscriber data;
    struct Node *next;
} Node;

Node* head = NULL;

int email_exists(const char *email) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->data.email, email) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void delete_email(const char *email) {
    Node *current = head;
    Node *prev = NULL;

    while (current != NULL && strcmp(current->data.email, email) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Email not found.\n");
        return;
    }

    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }
    
    free(current->data.email);
    free(current);
    printf("Unsubscribed successfully.\n");
}

void add_subscriber(const char *email) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data.email = strdup(email);
    new_node->next = head;
    head = new_node;
}

int main() {
    // Simulate adding subscribers
    add_subscriber("user1@example.com");
    add_subscriber("user2@example.com");

    char email[MAX_EMAIL_LENGTH];
    
    printf("Enter email to unsubscribe: ");
    fgets(email, MAX_EMAIL_LENGTH, stdin);
    email[strcspn(email, "\n")] = '\0'; // Remove newline character

    if (email_exists(email)) {
        delete_email(email);
    } else {
        printf("Email is not subscribed.\n");
    }

    return 0;
}