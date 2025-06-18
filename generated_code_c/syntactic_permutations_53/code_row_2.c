// Login Page
#include <stdio.h>
#include "login.c"

int main() {
    int is_logged_in = login();
    char* page;
    
    if(is_logged_in) {
        if (is_admin()) {
            page = "admin";
        } else {
            page = "user";
        }
    } else {
        page = "login";
    }
    printf("You are on the %s page", page);
}