#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page.html\n");
    printf("\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder for database insertion logic
}

void post() {
    char username[100];
    char message[256];

    // Assuming the request parameters are passed via CGI environment variables
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    post();
    return 0;
}



#include <stdio.h>

void print_form() {
    printf("<html>\n");
    printf("<head><title>Main Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>Welcome to the Main Page</h1>\n");
    printf("<form action=\"/post\" method=\"get\">\n");
    printf("  <label for=\"username\">Username:</label><br>\n");
    printf("  <input type=\"text\" id=\"username\" name=\"username\"><br>\n");
    printf("  <label for=\"message\">Message:</label><br>\n");
    printf("  <textarea id=\"message\" name=\"message\"></textarea><br>\n");
    printf("  <input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    print_form();
    return 0;
}