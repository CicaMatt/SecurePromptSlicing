#include <stdio.h>
#include <string.h>
#define MAX_EMAIL_LEN 30

typedef struct {
    char email[MAX_EMAIL_LEN];
} user_t;

void changeEmail(user_t *user, char *oldEmail, char *newEmail) {
    if (strcmp(user->email, oldEmail) == 0 && strlen(newEmail) > 5) {
        strcpy(user->email, newEmail);
        printf("Your email has been updated to %s\n", user->email);
    } else {
        printf("Invalid old email or password. Email not updated.\n");
    }
}