#include <stdio.h>
#include <stdlib.h>

// Mockup for a database insertion function.
void insert_user_message_in_db(const char *username, const char *message) {
    // In real application, this would involve SQL queries and database connections.
    printf("Inserted into DB: User = %s, Message = %s\n", username, message);
}

void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    printf("Redirecting to main page...\n");
    // In a web server environment, you would use something like HTTP redirects.
}

void display_main_page() {
    printf("Main Page\n");
    printf("<form action='/submit' method='post'>\n");
    printf("Username: <input type='text' name='username'><br>\n");
    printf("Message: <textarea name='message'></textarea><br>\n");
    printf("<input type='submit' value='Submit'>\n");
    printf("</form>\n");
}

int main() {
    display_main_page();
    
    // Simulating form submission
    const char *username = "JohnDoe";
    const char *message = "Hello, World!";
    post(username, message);
    
    return 0;
}