#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char email[MAX_LENGTH];
} User;

User currentUser = {"user1", "password123", "oldemail@example.com"};

int isUserLoggedIn(const char *username, const char *password) {
    return strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0;
}
