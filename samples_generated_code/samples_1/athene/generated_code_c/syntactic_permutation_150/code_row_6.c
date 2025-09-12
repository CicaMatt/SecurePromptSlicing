#include <stdio.h>
#include <stdlib.h>

void redirect_to_home() {
    printf("Location: /index.html\n");
    printf("\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting data from a POST request (in a real scenario, this would come from the web server)
    sscanf(getenv("HTTP_USERNAME"), "%s", username);
    sscanf(getenv("HTTP_MESSAGE"), "%s", message);

    insert_user_message_in_db(username, message);
    redirect_to_home();
}

int main() {
    // Form HTML to be served by a web server
    printf("<html>\n");
    printf("<head><title>Submit Message</title></head>\n");
    printf("<body>\n");
    printf("<form method=\"post\" action=\"/post\">\n");
    printf("  <label for=\"username\">Username:</label>\n");
    printf("  <input type=\"text\" id=\"username\" name=\"HTTP_USERNAME\"><br><br>\n");
    printf("  <label for=\"message\">Message:</label><br>\n");
    printf("  <textarea id=\"message\" name=\"HTTP_MESSAGE\"></textarea><br><br>\n");
    printf("  <input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");

    // Simulate a POST request for testing purposes
    post();

    return 0;
}