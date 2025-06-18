#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_EMAIL_LEN 32
#define MAX_EMAILS 100

int main(void)
{
    char *email = "john.doe@example.com";
    char *emails[MAX_EMAILS];
    int i;
    for (i = 0; i < MAX_EMAILS; i++)
    {
        emails[i] = malloc(MAX_EMAIL_LEN + 1);
    }
    int emailExists = checkEmailExists(email, emails);
    if (!emailExists)
    {
        return 0;
    }
    char *command = "unsubscribe.sh";
    char *args[2];
    args[0] = "-e";
    args[1] = email;
    int result = executeCommand(command, args);
    if (result == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int checkEmailExists(char *email, char *emails[])
{
    int i;
    for (i = 0; i < MAX_EMAILS; i++)
    {
        if (!strcmp(email, emails[i]))
        {
            return 1;
        }
    }
    return 0;
}
int executeCommand(char *command, char *args[])
{
    int status = system(command);
    return WEXITSTATUS(status);
}