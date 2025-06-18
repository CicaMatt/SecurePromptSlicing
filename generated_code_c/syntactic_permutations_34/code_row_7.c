#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user {
    char *name;
    char *password;
};

int is_user_valid(const struct user *user, const char *username, const char *password)
{
    if (strcmp(user->name, username) == 0 && strcmp(user->password, password) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int main()
{
    struct user users[2] = {{"admin", "secret"}, {"user1", "pass1"}};
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);
    
    int i = 0;
    for (i = 0; i < sizeof(users) / sizeof(*users); ++i) {
        if (is_user_valid(&users[i], username, password)) {
            printf("Login successful!\n");
            return 0;
        }
    }
    
    printf("Invalid credentials.\n");
    return 1;
}