#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
} Session;

void do_login(const char *input_username, const char *input_password) {
    const char correct_username[] = "admin";
    const char correct_password[] = "password123";

    if (strcmp(input_username, correct_username) == 0 &&
        strcmp(input_password, correct_password) == 0) {

        Session session;
        strcpy(session.username, input_username);
        
        printf("Login successful! Redirecting to secret page...\n");
        // In a real web application, redirect would be handled by the server
    } else {
        printf("Invalid username or password.\n");
    }
}

void index_page() {
    printf("Welcome!\n");
    printf("Please <a href='/login'>Login</a> to access secret settings.\n");
}

void secret_page(Session session) {
    if (strcmp(session.username, "") == 0) {
        printf("Unauthorized access. Please login first.\n");
    } else {
        printf("Secret settings\n");
    }
}

int main() {
    // Simulate navigating pages
    index_page();

    char input_username[MAX_USERNAME_LEN] = "admin";
    char input_password[MAX_PASSWORD_LEN] = "password123";

    Session session = {""};
    
    do_login(input_username, input_password);

    strcpy(session.username, input_username); // Assuming login was successful

    secret_page(session);
    
    return 0;
}