#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1024

typedef struct {
    char *username;
    char *email;
    int SSN;
} User;

void info(User user) {
    char buffer[SIZE];
    snprintf(buffer, SIZE, "Username: %s\nEmail: %s\nSSN: %d", user.username, user.email, user.SSN);
    printf("%s\n", buffer);
}