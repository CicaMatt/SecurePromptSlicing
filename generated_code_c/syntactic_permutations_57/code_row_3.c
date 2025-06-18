#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char *email;
    int passwd;
} user_t;

user_t users[10];
int numUsers = 0;

void addUser(char *email, int passwd)
{
    if (numUsers >= 10)
        return;
    user_t newUser;
    newUser.email = email;
    newUser.passwd = passwd;
    users[numUsers++] = newUser;
}

bool login(char *email, int passwd)
{
    for (int i = 0; i < numUsers; i++)
    {
        if (!strcmp(users[i].email, email) && users[i].passwd == passwd)
            return true;
    }
    return false;
}

void changeEmail(char *oldEmail, char *newEmail, int passwd)
{
    for (int i = 0; i < numUsers; i++)
    {
        if (!strcmp(users[i].email, oldEmail))
        {
            if (passwd == users[i].passwd)
            {
                users[i].email = newEmail;
                printf("Email changed\n");
            }
            else
                printf("Invalid password\n");
            break;
        }
    }
}

int main()
{
    addUser("test@example.com", 1234);
    login("test@example.com", 1234) ? printf("Logged in\n") : printf("Login failed\n");
    changeEmail("test@example.com", "newemail@example.com", 5678);
}