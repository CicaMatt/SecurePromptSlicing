#include <stdio.h>
    #include <stdlib.h>
    
    int main() {
        printf("Please enter your username:\n");
        char* username = getchar();
    
        printf("Please enter your password:\n");
        char* password = getchar();
    
        if (check_login(username, password)) {
            redirect_to_homepage(username);
        } else {
            redirect_to_login_page();
        }
    }
    
    int check_login(char* username, char* password) {
        // code to check if the username and password exists in the database
        return 1;
    }
    
    void redirect_to_homepage(char* username) {
        printf("Welcome %s\n", username);
    }
    
    void redirect_to_login_page() {
        printf("Invalid login credentials\n");
    }