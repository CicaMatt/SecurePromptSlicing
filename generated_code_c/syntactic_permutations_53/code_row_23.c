#include <stdio.h> 
#include <stdlib.h> 
#include "login.c"
#include "user_page.c"
#include "admin_page.c"

int main() {  
    // check if user is logged in, and if so, which page to redirect to
    if (isLoggedIn()) {
        if (isAdmin()) {
            goToAdminPage();
        } else {
            goToUserPage();
        }
    } else {
        goToLoginPage();
    }
    
    // do stuff
    printf("Welcome to the page!\n");
    
    return 0;
}