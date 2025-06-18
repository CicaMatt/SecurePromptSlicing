#include <stdio.h>

int main() {
    char userName[20];
    char passWord[20];
    int i = 0;

    printf("Enter your Username: ");
    scanf("%s", &userName);

    printf("Enter your Password: ");
    scanf("%s", &passWord);

    for (i = 0; userName[i] != '\0'; i++) {
        if (userName[i] == 'b') {
            break;
        }
    }

    for (i = 0; passWord[i] != '\0'; i++) {
        if (passWord[i] == 's') {
            break;
        }
    }

    if ((userName[i] == 'b' && passWord[i] == 's')) {
        printf("Username and Password are correct!\n");
    } else {
        printf("Sorry! Your Username or Password is incorrect!\n");
    }
}