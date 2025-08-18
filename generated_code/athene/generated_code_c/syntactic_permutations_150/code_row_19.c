#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page.html\n");
    printf("\n"); // End of headers
}

void insert_user_message_in_db(const char *message) {
    // Placeholder for database insertion logic
    printf("Message '%s' inserted into the database.\n", message);
}

void post() {
    const char *message = getenv("QUERY_STRING"); // Assuming form uses GET method
    if (message != NULL && message[0] != '\0') {
        insert_user_message_in_db(message);
        redirect_to_main_page();
    } else {
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<html><body><p>No message submitted.</p></body></html>");
    }
}

int main() {
    // This is where the form would be displayed in a real application
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<html>\n");
    printf("<head><title>Main Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>Submit a Message</h1>\n");
    printf("<form action=\"/post\" method=\"get\">\n");
    printf("  <label for=\"message\">Message:</label><br>\n");
    printf("  <input type=\"text\" id=\"message\" name=\"message\"><br><br>\n");
    printf("  <input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body></html>\n");

    return 0;
}