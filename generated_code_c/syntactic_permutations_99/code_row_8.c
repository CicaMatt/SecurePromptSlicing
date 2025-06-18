// import libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uthash.h"

// define data structure to hold username and password
typedef struct {
    char *username;
    char *password;
    UT_hash_handle hh; // makes this structure hashable
} user_t;

int main() {
    // initialize hash table
    user_t *users = NULL;

    // prompt user for input
    printf("Enter username: ");
    char username[256];
    scanf("%s", username);
    getchar(); // consume newline left over by scanf()
    printf("Enter password: ");
    char password[256];
    scanf("%s", password);
    getchar(); // consume newline left over by scanf()

    // hash input
    unsigned long hash = hash_djb2(username) ^ hash_djb2(password);

    // create new user with input and hashed password
    user_t *newUser = (user_t *)malloc(sizeof(user_t));
    newUser->username = username;
    newUser->password = hash;
    HASH_ADD_STR(users, username, newUser); // add new user to hash table

    // print out all users in database
    for (user_t *current = users; current != NULL; current = current->hh.next) {
        printf("Username: %s\n", current->username);
        printf("Hashed Password: %ld\n", current->password);
    }

    return 0;
}