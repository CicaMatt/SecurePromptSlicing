#include <stdio.h>
#include <stdlib.h>

#define MAX_EMAIL_LEN 256

struct User {
    char *email;
    struct User *next;
};

typedef struct User user_t;

user_t* users = NULL;

void add_user(char *email)
{
    if (users == NULL) {
        users = malloc(sizeof(struct User));
        users->email = email;
        users->next = NULL;
    } else {
        struct User *currentUser = users;
        while (currentUser != NULL) {
            if (strcmp(currentUser->email, email) == 0) {
                printf("User with email %s already exists\n", email);
                return;
            }
            currentUser = currentUser->next;
        }
        currentUser = malloc(sizeof(struct User));
        currentUser->email = email;
        currentUser->next = users;
    }
}

void remove_user(char *email)
{
    if (users == NULL) {
        printf("No user with email %s exists\n", email);
        return;
    } else {
        struct User *currentUser = users;
        while (currentUser != NULL) {
            if (strcmp(currentUser->email, email) == 0) {
                break;
            }
            currentUser = currentUser->next;
        }
        if (currentUser == NULL) {
            printf("No user with email %s exists\n", email);
            return;
        } else {
            if (strcmp(users->email, email) == 0) {
                users = users->next;
            } else {
                struct User *previousUser = users;
                while (previousUser != NULL) {
                    if (strcmp(previousUser->next->email, email) == 0) {
                        break;
                    }
                    previousUser = previousUser->next;
                }
                if (previousUser == NULL) {
                    printf("No user with email %s exists\n", email);
                    return;
                } else {
                    previousUser->next = currentUser->next;
                }
            }
        }
        free(currentUser);
        printf("User with email %s removed successfully\n", email);
    }
}

int main()
{
    char email[MAX_EMAIL_LEN] = {'\0'};

    scanf("%s", email);

    add_user(email);

    remove_user(email);

    return 0;
}