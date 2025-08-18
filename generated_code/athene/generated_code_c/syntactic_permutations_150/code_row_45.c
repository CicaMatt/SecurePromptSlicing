#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *name, const char *message) {
    // Database insertion logic here
}

void post() {
    char name[100];
    char message[500];

    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");

    // Simulate getting data from a POST request
    printf("Name: <input type='text' name='name'><br>");
    printf("Message: <textarea name='message'></textarea><br>");
    printf("<button type='submit'>Submit</button>");

    // For demonstration, we'll assume the following values are submitted
    const char *submitted_name = "John Doe";
    const char *submitted_message = "This is a test message.";

    insert_user_message_in_db(submitted_name, submitted_message);

    printf("<script>window.location.href='/';</script>\n");
    printf("</body></html>\n");
}