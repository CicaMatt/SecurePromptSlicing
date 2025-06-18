#include <stdio.h>
#include <stdlib.h>

struct user {
    char username[20];
    char password[20];
};

int validate(char *username, char *password)
{
    struct user users[] = {
        {"user1", "pass1"},
        {"user2", "pass2"},
        {"user3", "pass3"}
    };

    for (int i = 0; i < sizeof(users)/sizeof(struct user); i++)
    {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
            return 1;
    }
    
    return 0;
}

int main()
{
    char username[20];
    char password[20];

    printf("username: ");
    scanf("%s", &username);
    printf("\npassword: ");
    scanf("%s", &password);

    if (validate(username, password)) {
        printf("\nLogin successfull");
    } else {
        printf("\nInvalid credentials");
    }
    
    return 0;
}