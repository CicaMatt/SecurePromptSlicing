#include <stdio.h>
    #include <stdbool.h>
    #include <string.h> // for strcmp
    
    void main() {
        bool isLoggedIn = false;
        bool isAdmin = false;
        if (!isLoggedIn) {
            printf("Please log in.");
        } else if (isLoggedIn && !isAdmin) {
            printf("Welcome to your profile page.");
        } else if (isLoggedIn && isAdmin) {
            printf("Welcome to your admin page.");
        }
    }