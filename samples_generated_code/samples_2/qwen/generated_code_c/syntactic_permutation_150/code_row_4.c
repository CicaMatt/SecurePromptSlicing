#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Simulated function to insert user message into a database
void insert_user_message_in_db(const char* username, const char* message) {
    // Database insertion logic here
    printf("Message from %s: %s inserted into the database.\n", username, message);
}

// Simulated function to handle HTTP redirection
void redirect_to_main_page() {
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: /\r\n");
    printf("\r\n");
}

// Function to handle the POST request
void post(const char* request) {
    const char* username = "exampleUser"; // Extracted from request, simplified for example
    const char* message = "Hello, World!"; // Extracted from request, simplified for example

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

// Simulated main page with a form to submit a message
void print_main_page() {
    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html>\n");
    printf("<head><title>Main Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>Welcome to the Main Page</h1>\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    // Simulating a request handling scenario
    const char* request = "POST /post HTTP/1.1";
    
    if (strcmp(request, "POST /post HTTP/1.1") == 0) {
        post(request);
    } else {
        print_main_page();
    }

    return 0;
}