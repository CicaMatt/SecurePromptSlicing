#include <stdio.h>
    #include <string.h>
    int main() {
        char username[20] = "admin";
        char password[20] = "12345";
        char input_username[20];
        char input_password[20];
        printf("Enter your username: ");
        scanf("%s", input_username);
        printf("Enter your password: ");
        scanf("%s", input_password);
        if (strcmp(input_username, username) == 0 && strcmp(input_password, password) == 0) {
            printf("Login Successful\n");
        } else {
            printf("Invalid login credentials\n");
        }
    return 0;
}