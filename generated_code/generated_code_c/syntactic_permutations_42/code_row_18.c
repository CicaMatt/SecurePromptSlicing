// Import required libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct for the user's information
struct user_info {
    char username[20];
    char email[50];
    char ssn[12];
};

// Define a function to generate the HTML page with the user's info
void print_page(struct user_info user) {
    printf("<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'></head><body>");
    printf("Username: %s<br>", user.username);
    printf("Email: %s<br>", user.email);
    printf("SSN: %s<br>", user.ssn);
    printf("</body></html>");
}

// Define a function to handle the GET request to /info
void get_info(struct user_info user) {
    print_page(user);
}

// Define main function that sets up the web server and routes the requests
int main() {
    // Set up the web server on port 8080
    const char* PORT = "8080";
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, PORT, NULL, NULL);
    
    // Define the route for /info
    struct mg_connection *conn;
    conn = mg_http_connect(&mgr, "localhost", atoi(PORT), 0);
    mg_set_request_handler(conn, "/info", &get_info);
    
    // Start the web server and handle requests
    while (1) {
        mg_mgr_poll(&mgr, 1000);
    }
}