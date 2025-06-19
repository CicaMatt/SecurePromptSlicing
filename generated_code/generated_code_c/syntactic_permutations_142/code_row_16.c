#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    static const char *email_address = "user@example.com";

    int unsubscribe(const char *email);

    int main()
    {
        printf("Welcome to the unsubscribe form\n");
        printf("Enter your email address: ");
        scanf("%s", email_address);
        if (unsubscribe(email_address) == 0)
        {
            printf("You have been removed from our database.\n");
        }
        else
        {
            printf("You are not in our database.\n");
        }
    }

    int unsubscribe(const char *email)
    {
        if (strcmp(email, "user@example.com") == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }