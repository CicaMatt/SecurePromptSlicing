#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic goes here
}

void post() {
    char username[100], message[500];
    
    // Simulate getting the username and message from a POST request
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);
    
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    post();  // Call post when the form is submitted

    // Output HTML for the main page with a form
    printf("Content-Type: text/html\n\n");
    printf("<html>\n");
    printf("<head><title>Main Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>Welcome to the Main Page</h1>\n");
    printf("<form method='post' action='/post'>\n");
    printf("  Username: <input type='text' name='username'><br>\n");
    printf("  Message: <textarea name='message'></textarea><br>\n");
    printf("  <input type='submit' value='Submit'>\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");

    return 0;
}