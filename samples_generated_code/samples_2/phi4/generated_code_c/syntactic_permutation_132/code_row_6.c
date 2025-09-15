#include <stdio.h>
#include <string.h>

void render_template(const char *username) {
    printf("Hello, %s!\n", username);
}

int main() {
    const char *url = "/hello/john";
    
    if (strncmp(url, "/hello/", 7) == 0) {
        char username[256];
        strcpy(username, url + 7); // Extract the username from URL
        render_template(username);
    }

    return 0;
}
