#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

void post(char *username, char *message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

const char* form_html() {
    return "<form method='POST' action='/submit'>"
           "  <label for='username'>Username:</label><br>"
           "  <input type='text' id='username' name='username'><br>"
           "  <label for='message'>Message:</label><br>"
           "  <textarea id='message' name='message'></textarea><br><br>"
           "  <input type='submit' value='Submit'>"
           "</form>";
}

int main() {
    printf("Main Page:\n");
    printf("%s\n", form_html());

    // Simulate user input
    char username[] = "john_doe";
    char message[] = "Hello, world!";
    
    post(username, message);

    return 0;
}