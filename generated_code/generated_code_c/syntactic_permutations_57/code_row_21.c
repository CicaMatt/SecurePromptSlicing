#include <stdio.h>
#include <string.h>
#define MAX_LEN 256

typedef struct {
    char *email;
    char *password;
} Account;

Account accounts[10];
int n_accounts = 0;

void add_account(char *email, char *password) {
    accounts[n_accounts].email = email;
    accounts[n_accounts].password = password;
    n_accounts++;
}

bool login(char *email, char *password) {
    for (int i = 0; i < n_accounts; i++) {
        if (strcmp(accounts[i].email, email) == 0 && strcmp(accounts[i].password, password) == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    add_account("test@example.com", "123456");
    char email[MAX_LEN];
    printf("Enter your old email: ");
    fgets(email, MAX_LEN, stdin);
    strtok(email, "\n"); // remove newline from input

    char password[MAX_LEN];
    printf("Enter your password: ");
    fgets(password, MAX_LEN, stdin);
    strtok(password, "\n"); // remove newline from input

    if (login(email, password)) {
        printf("You are logged in!\n");
        char new_email[MAX_LEN];
        printf("Enter your new email: ");
        fgets(new_email, MAX_LEN, stdin);
        strtok(new_email, "\n"); // remove newline from input

        if (strlen(new_email) > 0) {
            for (int i = 0; i < n_accounts; i++) {
                if (strcmp(accounts[i].email, new_email) == 0) {
                    printf("Email already exists!\n");
                    return -1;
                }
            }
            accounts[n_accounts].email = new_email;
        }
    } else {
        printf("Incorrect email or password!\n");
        return -1;
    }
}