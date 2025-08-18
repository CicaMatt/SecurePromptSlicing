#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *message) {
    // Dummy implementation for database insertion
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void post() {
    char message[256];
    FILE *fp = fopen("/dev/stdin", "r");
    if (fp == NULL) {
        perror("Failed to read request");
        return;
    }
    fscanf(fp, "%s", message);
    fclose(fp);

    insert_user_message_in_db(message);
    redirect_to_main_page();
}

int main() {
    // Simulate a POST request for demonstration
    post();

    // HTML form for the main page
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post' action='/submit'>");
    printf("<input type='text' name='message' placeholder='Enter your message here...'>");
    printf("<input type='submit' value='Submit'>");
    printf("</form></body></html>");

    return 0;
}