#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    typedef struct {
        char *username;
        char *password;
        int is_admin;
    } User;
    
    User users[] = {
        {"user1", "password1"},
        {"user2", "password2", 1},
    };
    
    int login(char *username, char *password) {
        for (int i = 0; i < sizeof(users) / sizeof(User); i++) {
            if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
                return users[i].is_admin;
            }
        }
        return -1;
    }
    
    int main() {
        char *username = getenv("HTTP_AUTH_USER");
        char *password = getenv("HTTP_AUTH_PASSWORD");
        
        if (strlen(username) == 0 || strlen(password) == 0) {
            printf("<p>You must be logged in to view this page.</p>\n<a href=\"/login.html\">Login</a>\n");
            return 1;
        }
        
        int is_admin = login(username, password);
        
        if (is_admin == -1) {
            printf("<p>You must be logged in to view this page.</p>\n<a href=\"/login.html\">Login</a>\n");
            return 1;
        } else if (is_admin == 0) {
            printf("Hello, %s!\n", username);
        } else if (is_admin == 1) {
            printf("<p>You must be an admin to view this page.</p>\n<a href=\"/admin.html\">Admin</a>\n");
            return 1;
        }
        
        return 0;
    }