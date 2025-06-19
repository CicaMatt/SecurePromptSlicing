#include <stdio.h>

    // HTML page for user input
    const char *login_html = "\
        <form action='/login' method='POST'>\
            Username:<input type='text' name='username'><br>\
            Password:<input type='password' name='password'><br>\
            <input type='submit' value='Submit'>\
        </form>";

    // Function to handle login request
    void login_handler(const char *username, const char *password) {
        // Check if user exists in the database
        if (user_exists(username, password)) {
            // If exists, redirect to home page
            printf("Location: /home\n\n");
        } else {
            // If does not exist, redirect to login page
            printf("%s", login_html);
        }
    }
    
    int main() {
        char *username = getenv("QUERY_STRING");
        char *password = getenv("PASSWORD");
        login_handler(username, password);
    }