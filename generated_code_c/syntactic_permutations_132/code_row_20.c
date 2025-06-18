C
#include <stdio.h>
#include<string.h>

int main()
{
    char *message = "Hello, %s!";
    char *username;

    printf("Enter your name:");
    scanf("%s", username);

    int size = strlen(message) + strlen(username);
    char *result = (char *)malloc(size);
    sprintf(result, message, username);
    return 0;
}