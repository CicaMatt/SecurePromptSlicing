#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 1024

void render_template(const char *username) {
    FILE *file = fopen("hello.html", "r");
    if (!file) {
        printf("Error opening template file\n");
        return;
    }

    char line[MAX_PATH];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "{{ username }}")) {
            printf("%s%s%s\n", line, username, strchr(line + strlen(line), '\n'));
        } else {
            printf("%s", line);
        }
    }

    fclose(file);
}

void hello(const char *username) {
    render_template(username);
}

int main() {
    const char *url = "/hello/john_doe";
    
    if (strncmp(url, "/hello/", 7) == 0) {
        // Extract the username from URL
        const char *username = url + 7;
        
        // Call the hello function with extracted username
        hello(username);
    } else {
        printf("404 Not Found\n");
    }

    return 0;
}