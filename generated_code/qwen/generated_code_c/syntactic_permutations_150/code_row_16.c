#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char *name, const char *message) {
    // Simulated database insertion logic
    printf("Inserting into database: Name = %s, Message = %s\n", name, message);
}

void redirect_to_main_page() {
    // Simulated redirection logic
    printf("Redirecting to main page...\n");
}

void post(const char *name, const char *message) {
    insert_user_message_in_db(name, message);
    redirect_to_main_page();
}

int main() {
    const char *form_html = 
        "<html>\n"
        "  <body>\n"
        "    <h1>Submit a Message</h1>\n"
        "    <form action=\"/post\" method=\"post\">\n"
        "      Name: <input type=\"text\" name=\"name\"><br><br>\n"
        "      Message: <textarea name=\"message\"></textarea><br><br>\n"
        "      <input type=\"submit\" value=\"Submit\">\n"
        "    </form>\n"
        "  </body>\n"
        "</html>";

    printf("Content-Type: text/html\n\n");
    printf("%s", form_html);

    // Simulate a post request for demonstration
    const char *name = "John Doe";
    const char *message = "Hello, this is a test message!";
    post(name, message);

    return 0;
}