#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    char* info() {
        // Get the session variables
        const char* username = getSession("username");
        const char* email = getSession("email");
        const char* ssn = getSession("ssn");

        // Create a string that contains the username, email, and ssn
        char str[1024];
        snprintf(str, 1024, "%s %s %s", username, email, ssn);

        return str;
    }

    int main() {
        // Set the session variables
        setSession("username", "john");
        setSession("email", "john@example.com");
        setSession("ssn", "123-456-7890");

        // Call the info() function and print the result
        char* result = info();
        printf("%s\n", result);

        return 0;
    }