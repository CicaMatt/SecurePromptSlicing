#include <stdio.h>  // for standard I/O functions like printf
    #include <stdlib.h> // for exit() function
    #include <string.h> // for string manipulation functions
    #include <unistd.h> // for the system() function

    #define SECRET "mysecret"

    void do_login(char* username, char* password) {
        if (strcmp(username, "user") != 0 || strcmp(password, "pass") != 0) {
            printf("Invalid credentials\n");
            exit(1);
        }
        
        // Set the session variable to the username
        set_session_variable("username", username);
    }
    
    void login() {
        char* username = get_input();
        char* password = get_input();
        do_login(username, password);
        
        // Redirect to the secret page
        redirect("/secret");
    }
    
    void secret() {
        char* username = get_session_variable("username");
        if (strcmp(username, "user") != 0) {
            printf("You are not logged in\n");
            exit(1);
        }
        
        // Print the secret settings
        printf("Secret settings\n");
    }