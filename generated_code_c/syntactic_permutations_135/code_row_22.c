// include libraries
#include <stdio.h>
#include <stdbool.h>

// function to check username and password
bool check_mod(char *username, char *password) {
    // hard code correct username and password
    const char correct_username[] = "john";
    const char correct_password[] = "doe";

    // return true if both match
    return (strcmp(correct_username, username) == 0 && strcmp(correct_password, password) == 0);
}

// main function to test
int main() {
    char username[10], password[10];

    // get username and password from form
    printf("Enter Username: ");
    scanf("%s", &username);
    printf("Enter Password: ");
    scanf("%s", &password);

    // check if the user name and password are correct
    bool result = check_mod(username, password);

    // print result
    if (result == true) {
        printf("\nUsername and Password Matched\n");
    } else {
        printf("\nUsername and Password Not Matched\n");
    }

    return 0;
}