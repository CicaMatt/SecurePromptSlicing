#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
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
        if (content_length > 0) {
            char *data = malloc(content_length + 1);
            fread(data, 1, content_length, stdin);
            data[content_length] = '\0';

            sscanf(data, "username=%[^&]&message=%s", username, message);

            insert_user_message_in_db(username, message);
            free(data);
        }
    }

    redirect_to_main_page();
}

void print_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n");
    printf("<head><title>Main Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>Welcome to the Main Page</h1>\n");
    printf("<form method='post' action='/post'>\n");
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
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        post();
    } else {
        print_form();
    }

    return 0;
}