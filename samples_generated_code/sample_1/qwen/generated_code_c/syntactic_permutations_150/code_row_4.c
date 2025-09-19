#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char* username, const char* message) {
    // Simulated database insertion function
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
}

void redirect_to_main_page() {
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: /\r\n");
    printf("\r\n");
}

void post(const char* request) {
    const char* username = strstr(request, "username=");
    const char* message = strstr(request, "message=");

    if (username && message) {
        username += strlen("username=");
        message += strlen("message=");
        
        // Find the end of the username and message
        char temp_username[100], temp_message[100];
        sscanf(username, "%[^&]", temp_username);
        sscanf(message, "%s", temp_message);

        insert_user_message_in_db(temp_username, temp_message);
    }

    redirect_to_main_page();
}

void print_main_page() {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html><body>");
    printf("<h1>Submit a Message</h1>");
    printf("<form method=\"post\" action=\"/post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Message: <textarea name=\"message\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");
}

int main() {
    // Simulated request handling
    const char* request = "POST /post HTTP/1.1\r\nContent-Length: 34\r\n\r\nusername=johndoe&message=HelloWorld";
    
    if (strstr(request, "POST")) {
        post(request);
    } else {
        print_main_page();
    }

    return 0;
}