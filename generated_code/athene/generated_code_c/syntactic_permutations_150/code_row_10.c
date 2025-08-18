#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder for database insertion logic
}

void handle_submit() {
    char username[100], message[500];
    
    // Simulate getting the username and message from a request (e.g., POST data)
    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");
    
    scanf("%99s", username);
    scanf("%499[^\n]", message);

    insert_user_message_in_db(username, message);

    // Redirect the user back to the main page
    printf("<script>window.location.href='/';</script>");
    printf("</body></html>\n");
}

int main() {
    // Simulate a web server environment where handle_submit is called on form submit
    printf("Simulating form submission...\n");
    handle_submit();
    
    return 0;
}