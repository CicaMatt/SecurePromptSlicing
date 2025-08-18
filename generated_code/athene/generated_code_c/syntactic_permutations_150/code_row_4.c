#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void post() {
    char username[100], message[500];
    
    // Simulate getting data from request (for simplicity, using fixed strings)
    const char *request_data = "username=JohnDoe&message=Hello%20World";
    sscanf(request_data, "username=%[^&]&message=%s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    post(); // This would be called when the form is submitted
    return 0;
}