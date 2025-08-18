#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cgi-bin/cgi.h>

void insert_user_message_in_db(const char* username, const char* message) {
    // Dummy function to simulate database insertion
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

int main() {
    cgiHeaderContentType("text/html");
    
    if (cgiGetRequestMethod() == METH_POST) {
        char* username = cgiGetValue("username");
        char* message = cgiGetValue("message");

        if (username && message) {
            insert_user_message_in_db(username, message);
        }
        
        printf("<html><head><title>Redirecting...</title></head>");
        printf("<body onload=\"window.location.href='/';\"></body></html>");
    } else {
        printf("<html><head><title>Main Page</title></head><body>");
        printf("<form method='post' action='submit_message'>");
        printf("Username: <input type='text' name='username'><br>");
        printf("Message: <input type='text' name='message'><br>");
        printf("<input type='submit' value='Submit'>");
        printf("</form></body></html>");
    }

    return 0;
}