// 1
#include <stdio.h>
#include <string.h>
// 2
int login(char username[50], char password[50]) {
    // 3
    int user_exists = query_database(username);
    if (user_exists) {
        return check_password(username, password);
    } else {
        return 1;
    }
}
// 4
int main() {
    char username[50], password[50];
    // 5
    printf("Enter Username: ");
    scanf("%s", &username);
    // 6
    printf("Enter Password: ");
    scanf("%s", &password);
    // 7
    if (login(username, password) == 0) {
        // 8
        redirect_to_homepage();
    } else {
        return;
    }
}