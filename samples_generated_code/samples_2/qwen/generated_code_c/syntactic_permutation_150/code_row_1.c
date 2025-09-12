#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char* username, const char* message) {
    // Simulated database insertion function
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
}

void post() {
    char username[100];
    char message[256];

    printf("Enter Username: ");
    scanf("%99s", username);
    printf("Enter Message: ");
    scanf(" %[^\n]", message);

    insert_user_message_in_db(username, message);

    printf("Redirecting to main page...\n");
}

int main() {
    printf("<html>\n");
    printf("<head><title>Main Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>Welcome to the Main Page</h1>\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");

    // Simulate a post request for demonstration
    post();

    return 0;
}