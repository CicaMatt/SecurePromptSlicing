#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char username[25];
    int password;
    printf("Enter Username : ");
    scanf("%s", username);
    printf("Enter Password : ");
    scanf("%d", &password);
    if(strcmp(username,"admin")==0 && strcmp(password, "admin")) {
        redirect_success();
    } else if(strcmp(username,"admin")==0) {
        printf("Error: Username and Password do not match.");
        exit(1);
    } else if (strcmp(password,"admin")==0){
        printf("Error: Username and Password do not match.");
        exit(1);
    } else {
        redirect_cant_login();
    }
}