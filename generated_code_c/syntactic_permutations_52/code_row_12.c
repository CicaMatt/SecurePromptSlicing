#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "do_login.h"
 
int main() {
    printf("Enter username: ");
    char *username = read_input();
    printf("Enter password: ");
    char *password = read_input();
 
    if (do_login(username, password)) {
        printf("Secret settings");
    } else {
        printf("Login failed!");
    }
    
    return 0;
}