#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting data from a POST request (CGI)
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fread(username, sizeof(char), 100, stdin);
        fread(message, sizeof(char), 500, stdin);

        // Remove trailing null characters
        username[99] = '\0';
        message[499] = '\0';

        insert_user_message_in_db(username, message);
    }

    redirect_to_main_page();
}

int main() {
    post();
    return 0;
}



#include <stdio.h>

void show_main_page_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n");
    printf("<head><title>Main Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>Welcome to the Main Page</h1>\n");
    printf("<form method='post' action='/submit'>\n");
    printf("  <label for='username'>Username:</label>\n");
    printf("  <input type='text' id='username' name='username'><br><br>\n");
    printf("  <label for='message'>Message:</label><br>\n");
    printf("  <textarea id='message' name='message'></textarea><br><br>\n");
    printf("  <input type='submit' value='Submit'>\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    show_main_page_form();
    return 0;
}