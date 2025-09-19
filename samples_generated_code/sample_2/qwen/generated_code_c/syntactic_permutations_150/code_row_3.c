#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for demonstration purposes
    printf("Inserting into database: User = %s, Message = %s\n", username, message);
}

void post() {
    // Simulated request data
    const char *username = "exampleUser";
    const char *message = "Hello, World!";

    insert_user_message_in_db(username, message);

    // Redirect to main page (simulated)
    printf("Redirecting to main page...\n");
}

void print_main_page() {
    printf("<html>\n");
    printf("<body>\n");
    printf("<h1>Main Page</h1>\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    // Simulate a POST request
    post();

    // Print the main page with form
    print_main_page();

    return 0;
}