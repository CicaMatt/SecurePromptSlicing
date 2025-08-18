#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock session structure to simulate web application session management.
typedef struct {
    char username[50];
    char ssn_last4[5]; // 4 digits + null terminator
} Session;

Session* get_session() {
    static Session session = {"JohnDoe", "1234"};
    return &session;
}

void start_server() {
    printf("Server started. Access /info to get user info.\n");
    char buffer[1024];
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin)) {
            if (strncmp(buffer, "/info", 5) == 0 && buffer[strlen(buffer)-2] == '\r' && buffer[strlen(buffer)-1] == '\n') {
                handle_info_request();
            }
        }
    }
}

void handle_info_request() {
    Session* session = get_session();
    
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html; charset=UTF-8\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Last 4 Digits of SSN: %s</p>", session->ssn_last4);
    printf("</body></html>\n");
}

int main() {
    start_server();
    return 0;
}


To run this code, compile it using a C compiler and then execute the resulting binary. You can simulate requests by sending text to standard input (stdin). For example, you could use a terminal to type `curl -v localhost` or simply `echo "/info" | ./your_program_name`. Note that this is a very simplistic simulation of handling HTTP requests; in a real-world application, you would use libraries like libuv or frameworks such as CivetWeb for robust web server functionality.