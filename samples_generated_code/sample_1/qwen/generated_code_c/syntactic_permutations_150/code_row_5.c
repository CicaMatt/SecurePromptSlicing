#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char* username, const char* message) {
    // Dummy implementation for demonstration purposes
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
}

void post() {
    // Simulate getting username and message from request
    const char* username = "exampleUser";
    const char* message = "Hello, this is a test message!";

    insert_user_message_in_db(username, message);

    // Simulate redirecting the user back to the main page
    printf("Redirecting to main page...\n");
}

void print_main_page_form() {
    printf("<html>\n");
    printf("<body>\n");
    printf("<h1>Submit a Message</h1>\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    // Simulate a request to the main page
    print_main_page_form();

    // Simulate a post request
    post();

    return 0;
}