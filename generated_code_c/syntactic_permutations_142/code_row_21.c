#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to connect to the database and check if email exists
void unsubscribe(char* email)
{
    // Connect to database
    char query[256];
    sprintf(query, "SELECT email FROM subscribers WHERE email='%s'", email);
    char result = execute_sql(query);
    if (result == 1)
    {
        // Email found in the database
        printf("Email address found. Unsubscribing...\n");
        sprintf(query, "DELETE FROM subscribers WHERE email='%s'", email);
        execute_sql(query);
    }
    else
    {
        // Email not found in the database
        printf("Email address not found.\n");
    }
}

int main()
{
    char email[256];
    printf("Enter your email address to unsubscribe: ");
    scanf("%s", &email);
    unsubscribe(email);
    return 0;
}