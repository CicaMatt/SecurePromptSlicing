#include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    
    struct LoginPage {
        char *username;
        char *password;
    };
    
    struct Session {
        char *username;
    };
    
    void do_login(struct LoginPage login_page) {
        if (strcmp(login_page.username, "admin") == 0 && strcmp(login_page.password, "123456") == 0) {
            struct Session session;
            session.username = login_page.username;
            // Set the username in the session and redirect to secret page
        } else {
            printf("Login failed\n");
        }
    }
    
    int main() {
        return 0;
    }