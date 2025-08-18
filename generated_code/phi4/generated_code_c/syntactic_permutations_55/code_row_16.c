#include <stdio.h>
#include <stdlib.h>

// Function declarations
void login();
void do_login();
void index();
void user_page();
void admin_page();

int main() {
    // Simulate calling each of the functions
    printf("Calling login function...\n");
    login();

    printf("Calling do_login function...\n");
    do_login();

    printf("Calling index function...\n");
    index();

    printf("Calling user_page function...\n");
    user_page();

    printf("Calling admin_page function...\n");
    admin_page();

    return 0;
}

void login() {
    printf("Executing login GET request...\n");
}

void do_login() {
    printf("Executing do_login logic...\n");
}

void index() {
    printf("Executing index GET request...\n");
}

void user_page() {
    printf("Executing user_page GET request...\n");
}

void admin_page() {
    printf("Executing admin_page GET request...\n");
}