#include <stdio.h>
#include <string.h>

void do_login(const char *username, const char *password);
void show_index();
void show_secret();

char session_username[50] = {0};

int main() {
    int choice;
    printf("Choose an option:\n1. Index Page\n2. Login Page\n3. Secret Page\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            show_index();
            break;
        case 2: {
            char username[50], password[50];
            printf("Enter Username: ");
            scanf("%s", username);
            printf("Enter Password: ");
            scanf("%s", password);
            do_login(username, password);
            break;
        }
        case 3:
            if (strlen(session_username) > 0) {
                show_secret();
            } else {
                printf("Please login first.\n");
            }
            break;
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        strcpy(session_username, username);
        printf("Login successful. Redirecting to secret page...\n");
        show_secret();
    } else {
        printf("Invalid credentials.\n");
    }
}

void show_index() {
    printf("Index Page:\n");
    printf("Click here to [Login](#)\n");
}

void show_secret() {
    if (strlen(session_username) > 0) {
        printf("Secret Settings\n");
    } else {
        printf("Access Denied. Please login first.\n");
    }
}