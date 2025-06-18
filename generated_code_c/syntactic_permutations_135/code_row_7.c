#include <stdio.h>
#include <string.h>
#include <stdbool.h> 

bool check_mod(char *name, char *password) {
    if (strcmp(name, "admin") == 0 && strcmp(password, "admin") == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    // code for getting name and password from the form.
    char name[512];
    char password[512];
    
    if (check_mod(name, password)) {
        printf("Welcome to admin page");
    } else {
        printf("Invalid login credentials");
    }
    return 0;
}