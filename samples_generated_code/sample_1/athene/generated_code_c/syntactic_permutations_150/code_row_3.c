#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder for database insertion logic
}

void post() {
    char username[100];
    char message[500];

    printf("Content-Type: text/html\n\n");

    // Simulate getting the username and message from a form submission
    sscanf(getenv("QUERY_STRING"), "username=%99[^&]&message=%499s", username, message);

    insert_user_message_in_db(username, message);

    printf("<html><head><meta http-equiv='refresh' content='0;url=/main'></head>");
    printf("<body></body></html>");
}

int main() {
    post();
    return 0;
}



#include <stdio.h>

void print_main_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n");
    printf("<head><title>Message Board</title></head>\n");
    printf("<body>\n");
    printf("<h1>Submit a Message</h1>\n");
    printf("<form method='POST' action='/post'>\n");
    printf("Username: <input type='text' name='username'><br>\n");
    printf("Message: <textarea name='message'></textarea><br>\n");
    printf("<input type='submit' value='Submit'>\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    print_main_page();
    return 0;
}