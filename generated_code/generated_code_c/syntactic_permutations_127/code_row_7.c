#include <stdio.h>
#include <string.h>
#define MAX_USERNAME 20

int main(void)
{
    char username[MAX_USERNAME + 1];
    fgets(username, MAX_USERNAME, stdin);
    int len = strlen(username);
    if (username[len - 1] == '\n')
        username[len - 1] = '\0';

    char response[2 * MAX_USERNAME];
    sprintf(response, "Hello %s", username);

    fputs(response, stdout);
}