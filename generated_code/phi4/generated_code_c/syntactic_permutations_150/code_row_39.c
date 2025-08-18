#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated request structure for demonstration
typedef struct {
    char username[50];
    char message[256];
} Request;

// Function prototype declarations
void post(Request *req);
int insert_user_message_in_db(const char *username, const char *message);
void redirect_to_main_page();

// Main function to simulate user interaction
int main() {
    // Simulate a user submitting a message
    Request req;
    strcpy(req.username, "user123");
    strcpy(req.message, "Hello, World!");

    post(&req);

    return 0;
}

void post(Request *req) {
    if (insert_user_message_in_db(req->username, req->message)) {
        printf("Message inserted successfully.\n");
        redirect_to_main_page();
    } else {
        printf("Failed to insert message.\n");
    }
}

int insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion
    printf("Inserting into DB: Username = %s, Message = %s\n", username, message);
    return 1; // Return 1 for success, 0 for failure (simulated)
}

void redirect_to_main_page() {
    printf("Redirecting to the main page...\n");
}

// HTML form representation in C
const char *html_form = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
</head>
<body>
    <h1>Welcome to the Main Page</h1>
    <form action="/submit_message" method="post">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br>
        <label for="message">Message:</label><br>
        <textarea id="message" name="message"></textarea><br><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>
)";

void display_main_page() {
    printf("%s\n", html_form);
}

// Simulate displaying the main page with a form
int simulate_web_server() {
    // Display the main page with form
    display_main_page();
    
    return 0;
}