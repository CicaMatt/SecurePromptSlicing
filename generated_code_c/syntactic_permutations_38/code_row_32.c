#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    char *username = malloc(sizeof(char) * 100);
    char *password = malloc(sizeof(char) * 100);
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);
    
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456789")) {
        redirect("/dashboard");
    } else {
        redirect("/login");
    }
    
    return 0;
}