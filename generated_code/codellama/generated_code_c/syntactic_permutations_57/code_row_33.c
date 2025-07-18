#include <stdio.h> 
    #include <stdlib.h>
    #include <string.h>
    
    struct User {
        char *email;
        char *password;
    };
    
    struct Login {
        char *email;
        char *password;
    };
    
    int is_logged_in(struct Login login, struct User user) {
        if (strcmp(login.email, user.email) == 0 && strcmp(login.password, user.password) == 0) {
            return 1;
        } else {
            return 0;
        }
    };
    
    int is_valid_email(char *new_email) {
        char *at = strchr(new_email, '@');
        if (!at || at == new_email || !strchr(at + 1, '.')) {
            return 0;
        } else {
            return 1;
        }
    };
    
    struct User *create_user(char *email, char *password) {
        struct User *user = malloc(sizeof(struct User));
        user->email = email;
        user->password = password;
        return user;
    };
    
    int change_email(struct Login login, struct User user, char *new_email, char *confirm_password) {
        if (!is_logged_in(login, user)) {
            printf("You must be logged in to change your email.");
            return 0;
        } else if (strcmp(user.password, confirm_password) != 0) {
            printf("Invalid confirm password.");
            return 0;
        } else if (!is_valid_email(new_email)) {
            printf("Invalid new email");
            return 0;
        } else {
            user.email = new_email;
            return 1;
        }
    };
    
    struct User *user = create_user("test@example.com", "password");
    if (change_email((struct Login){"test@example.com", "password"}, *user, "new@example.com", "password")) {
        printf("%s", user->email);
    } else {
        printf("Error changing email");
    };