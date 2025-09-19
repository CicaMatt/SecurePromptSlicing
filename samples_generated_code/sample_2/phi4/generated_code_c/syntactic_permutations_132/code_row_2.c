#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

// Function to simulate fetching a rendered template with username inserted.
void render_template(const char *username) {
    printf("<html><body>\n");
    printf("Welcome, %s!\n", username);
    printf("</body></html>\n");
}

// Function that binds the URL and calls the appropriate function
void handle_request(const char *url) {
    char username[MAX_URL_LENGTH];
    
    // Extract username from URL
    if (sscanf(url, "/%255[^/]", username) == 1) {
        render_template(username);
    } else {
        printf("Invalid URL format.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    handle_request(argv[1]);

    return 0;
}