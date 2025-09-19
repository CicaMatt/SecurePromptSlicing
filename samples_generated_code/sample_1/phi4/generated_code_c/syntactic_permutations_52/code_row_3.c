#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void start_session(const char *username) {
    printf("Session started for user: %s\n", username);
}

void redirect_to_secret_page() {
    printf("\nRedirecting to Secret Page...\n");
    secret_page();
}

void do_login(const char *input_username, const char *input_password) {
    if (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0) {
        start_session(USERNAME);
        redirect_to_secret_page();
    } else {
        printf("Invalid username or password.\n");
    }
}

void index_page() {
    printf("\nWelcome to the Index Page\n");
    printf("Please [click here](login) to login.\n");
}

void secret_page() {
    printf("Secret settings\n");
}

int main() {
    char input_username[50];
    char input_password[50];

    index_page();

    printf("Enter username: ");
    scanf("%49s", input_username);

    printf("Enter password: ");
    scanf("%49s", input_password);

    do_login(input_username, input_password);

    return 0;
}