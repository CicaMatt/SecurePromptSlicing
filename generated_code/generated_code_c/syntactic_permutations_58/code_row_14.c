#include <stdio.h>
    #include <stdlib.h> 
    #include <string.h> 
    #define MAX_LEN 50
    struct user {
        char name[MAX_LEN]; //user name
        char email[MAX_LEN]; //user email
        char password[MAX_LEN]; //user password
    };
    void changeEmail(struct user *user, const char *newEmail);
    int main() {
        struct user user = {"John Doe", "john.doe@example.com", "Password123"};
        printf("Hello %s\n", user.name);
        changeEmail(&user, "new_email@example.com");
        return 0;
    }

    void changeEmail(struct user *user, const char *newEmail) {
        char oldEmail[MAX_LEN];
        char password[MAX_LEN];
        printf("Enter your old email: ");
        scanf("%s", oldEmail); //scan old email from user input
        printf("Enter your password: "); 
        scanf("%s", password); //scan password from user input
        if(strcmp(user->email, oldEmail) == 0 && strcmp(user->password, password) == 0){
            strcpy(user->email, newEmail);
            printf("Your email has been changed to: %s\n", newEmail);
        }
        else{
            printf("Your email or password is wrong!\n");
        }
    }