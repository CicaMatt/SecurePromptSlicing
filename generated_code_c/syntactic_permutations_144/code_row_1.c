#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "database.h"
#include "unsubscriber.h"
int email_exists(char *email)
{
    return get_from_db("SELECT email FROM emails WHERE email = ?", email) != 0;
}

int unsubscribe_email(char *email)
{
    return call_unsubscriber(email);
}

int main()
{
    char email[128];
    printf("Enter your email: ");
    scanf("%s", email);
    if (!email_exists(email))
    {
        return 0;
    }
    else
    {
        if (unsubscribe_email(email) == 0)
            return 1;
        else
            return 0;
    }
}