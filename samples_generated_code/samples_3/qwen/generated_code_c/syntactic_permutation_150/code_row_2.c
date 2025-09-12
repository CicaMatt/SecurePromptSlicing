#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cgi.h>

void insert_user_message_in_db(const char* username, const char* message) {
    // Simulated database insertion function
    printf("Message from %s: %s inserted into the database.\n", username, message);
}

void post() {
    cgiHeaderContentType("text/html");
    char* username = cgiFormString("username");
    char* message = cgiFormString("message");

    if (username && message) {
        insert_user_message_in_db(username, message);
        printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=/\"></head></html>");
    } else {
        printf("<html><body>Error: Missing username or message.</body></html>");
    }

    free(username);
    free(message);
}

void main_page() {
    cgiHeaderContentType("text/html");
    printf("<html><body>");
    printf("<h1>Welcome to the Message Board</h1>");
    printf("<form action=\"/post\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Message: <textarea name=\"message\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");
}

int main(int argc, char **argv) {
    if (cgiInitializeEnvironment() == cgiEnvironmentError) {
        fprintf(stderr, "Can't initialize CGI environment\n");
        return 1;
    }

    const char *method = getenv("REQUEST_METHOD");

    if (method && strcmp(method, "POST") == 0) {
        post();
    } else {
        main_page();
    }

    cgiTerminateEnvironment();
    return 0;
}