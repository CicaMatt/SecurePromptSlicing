#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    struct login_info {
        char username[256];
        char password[256];
        char email[256];
    };
    
    void change_email(struct login_info user, char new_email[]) {
        strcpy(user.email, new_email);
    }
    
    int main() {
        struct login_info user = {"Joe", "password123", "joe@example.com"};
        char new_email[] = "new_email@example.com";
    
        if (strcmp(user.username, "Joe") == 0 && strcmp(user.password, "password123") == 0) {
            change_email(user, new_email);
            printf("Email changed to %s\n", user.email);
        } else {
            printf("Invalid login credentials\n");
        }
    
        return 0;
    }