#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <string.h>
    #include <regex.h>
    #include <time.h>
    #include <sys/stat.h>

    int main() {
        // Declare variables for username, email and SSN
        char *username, *email, *ssn;
        // Read the username, email and SSN from session
        session_start();
        username = $_SESSION['username'];
        email = $_SESSION['email'];
        ssn = $_SESSION['ssn'];
        // Check if all the variables are set
        if (username && email && ssn) {
            printf("Username: %s\n", username);
            printf("Email: %s\n", email);
            printf("SSN: %s\n", ssn);
        }
    }