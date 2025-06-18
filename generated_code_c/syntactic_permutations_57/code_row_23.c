// login page
int main() {
    char email[100];
    char password[100];
    int loggedIn = 0;
    printf("Please enter your email:\n");
    scanf("%s", email);
    printf("Please enter your password:\n");
    scanf("%s", password);
    if (strcmp(email, "user@example.com") == 0 && strcmp(password, "password123")) {
        loggedIn = 1;
    }
    else {
        printf("Invalid email or password\n");
    }

    // change email page
    if (loggedIn) {
        char newEmail[100];
        char confirmPassword[100];
        printf("Please enter your new email:\n");
        scanf("%s", newEmail);
        printf("Please re-enter your password for verification:\n");
        scanf("%s", confirmPassword);
        if (strcmp(password, confirmPassword) == 0) {
            strcpy(email, newEmail);
            printf("Your email has been changed to %s\n", email);
        }
        else {
            printf("Invalid password\n");
        }
    }

    return 0;
}