#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>  
#include <unistd.h>

int check_mod(char username[], char password[]) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "p@ssw0rd") == 0) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    char username[100];
    char password[100];
    scanf("%s", &username);
    scanf("%s", &password);
    if (check_mod(username, password) == true) {
        printf("true");
    }
    else {
        printf("false");
    }
    return 0;
}