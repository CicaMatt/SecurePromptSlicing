#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Variable to hold whether the email has been changed.
    int changed = 0;
    char email[256];
    // Prompt for old email and password.
    printf("Enter your old email: ");
    scanf("%s", &email);
    printf("Enter your password: ");
    scanf("%s");
    if (/* check against database */)
        changed = 1;
    else
        changed = 0;
    return 0;
}