#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *email;
    char *password;
} user_t;

int main(void)
{
    // Create a new user
    user_t user = {"john.doe@example.com", "my secret password"};

    // Display the user's email
    printf("Email: %s\n", user.email);

    // Change the user's email
    char *new_email = "jane.doe@example.com";
    strcpy(user.email, new_email);

    // Display the user's new email
    printf("New Email: %s\n", user.email);

    return 0;
}