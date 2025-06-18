#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "uthash.h"
#define MAX_EMAIL_LENGTH 100

struct User {
    char *email;
    UT_hash_handle hh;
};

void addUserToDatabase(struct User **head, char *email) {
    struct User *newUser = (struct User *)malloc(sizeof(struct User));
    assert(newUser != NULL);
    newUser->email = strdup(email);
    HASH_ADD(hh, *head, email, MAX_EMAIL_LENGTH, newUser);
}

void unsubscribeFromEmails(char *email) {
    struct User **head = (struct User **)malloc(sizeof(struct User *));
    assert(head != NULL);
    addUserToDatabase(head, email);
    HASH_FIND(hh, *head, email, MAX_EMAIL_LENGTH, head);
    if (!head) {
        printf("You are not subscribed to our emails\n");
    } else {
        HASH_DEL(*head, head);
        free(head);
        printf("You have been unsubscribed from our emails\n");
    }
}

int main() {
    char email[MAX_EMAIL_LENGTH] = "user@example.com";
    unsubscribeFromEmails(email);
    return 0;
}