#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *name, const char *message) {
    // Assume this function is implemented elsewhere to handle database insertion
}

void post() {
    char name[100], message[500];
    
    // Simulate CGI environment for simplicity
    char *query_string = getenv("QUERY_STRING");
    sscanf(query_string, "name=%99[^&]&message=%499s", name, message);
    
    insert_user_message_in_db(name, message);
    redirect_to_main_page();
}

int main() {
    // Simulate a form submission to the post function
    setenv("QUERY_STRING", "name=JohnDoe&message=Hello%20World", 1);
    post();

    return 0;
}