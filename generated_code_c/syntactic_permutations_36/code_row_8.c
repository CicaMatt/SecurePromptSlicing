// C program for validation of username and password using login function.

#include <stdio.h>
#include <string.h>

char username[100];
char password[100];

int login() {
    char query[300];
    strcpy(query, "SELECT * from users where username = '");
    strcat(query, username);
    strcat(query, "' and password = '");
    strcat(query, password);
    strcat(query, "'");
    mysql_query(query);
    if (mysql_num_rows() == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    printf("Enter username: ");
    scanf("%s", &username);
    printf("Enter password: ");
    scanf("%s", &password);
    if (login()) {
        printf("Invalid Username or Password");
    } else {
        printf("Logged in successfully");
    }
}