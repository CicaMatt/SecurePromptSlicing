#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_MESSAGE_LENGTH 256

void insert_user_message_in_db(const char* username, const char* message) {
    // Dummy function to simulate database insertion
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

void post() {
    char username[MAX_USERNAME_LENGTH];
    char message[MAX_MESSAGE_LENGTH];

    // Simulate getting data from a request
    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter message: ");
    fgets(message, MAX_MESSAGE_LENGTH, stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline character

    insert_user_message_in_db(username, message);

    // Simulate redirecting back to the main page
    printf("Redirecting back to the main page...\n");
}

void display_main_page() {
    printf("<html>\n");
    printf("<head><title>Main Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>Welcome to the Main Page</h1>\n");
    printf("<form action=\"post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    display_main_page();
    post(); // Simulate form submission
    return 0;
}