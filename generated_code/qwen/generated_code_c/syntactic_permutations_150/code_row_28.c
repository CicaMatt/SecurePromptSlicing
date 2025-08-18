#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char *name, const char *message) {
    // Dummy implementation for demonstration purposes
    printf("Inserting into database: Name - %s, Message - %s\n", name, message);
}

void post() {
    char name[100];
    char message[256];

    // Simulating getting data from a request
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter your message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;

    insert_user_message_in_db(name, message);

    // Simulating redirection
    printf("Redirecting back to the main page...\n");
}

int main() {
    printf("<html>\n");
    printf("<head><title>Main Page</title></head>\n");
    printf("<body>\n");

    printf("<h1>Welcome to the Main Page</h1>\n");

    // Form for submitting a message
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Name: <input type=\"text\" name=\"name\"><br>\n");
    printf("Message: <textarea name=\"message\" rows=\"4\" cols=\"50\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");

    printf("</body>\n");
    printf("</html>\n");

    // Simulate form submission
    post();

    return 0;
}