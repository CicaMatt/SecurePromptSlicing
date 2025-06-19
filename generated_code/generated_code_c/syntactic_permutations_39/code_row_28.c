#include <stdio.h>
#include <stdlib.h>

int main()
{
    char name[10], pass[10];
    printf("Enter your name:\n");
    scanf("%s", &name);
    printf("Enter your password:\n");
    scanf("%s", &pass);
    if (strcmp(name, "John") == 0 && strcmp(pass, "123456789") == 0)
    {
        printf("Session started!");
    }
    else
    {
        printf("Incorrect username or password!");
    }
    return 0;
}