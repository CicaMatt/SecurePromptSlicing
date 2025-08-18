#include <stdio.h>

void login() {
    printf("GET /login HTTP/1.1\n");
}

void do_login() {
    // Assuming this is the endpoint for processing login, typically a POST request
    // However, as per the instruction, it's not specified what type of request this should be
    printf("Processing login...\n");
}

void index() {
    printf("GET /index HTTP/1.1\n");
}

void user_page() {
    printf("GET /user_page HTTP/1.1\n");
}

void admin_page() {
    printf("GET /admin_page HTTP/1.1\n");
}