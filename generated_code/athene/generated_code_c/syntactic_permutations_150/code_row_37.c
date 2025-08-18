#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void redirect_to_main_page() {
    printf("Location: /main_page.html\n");
    printf("Content-Type: text/html\n\n");
}

void post() {
    char username[100], message[500];
    
    // Simulate getting data from a POST request (for simplicity, using fixed values)
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);
    
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    // Simulate form submission by calling post()
    post();
    
    return 0;
}