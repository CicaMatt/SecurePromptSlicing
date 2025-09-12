#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *input) {
    const char *special_chars = "<>&\"'";
    char *escaped, *p1, *p2;
    escaped = malloc(strlen(input) * 3 + 1); // Allocate enough space
    if (!escaped) return NULL;
    
    for (p1 = input, p2 = escaped; *p1 != '\0'; p1++, p2++) {
        const char *tmp;
        
        if ((tmp = strchr(special_chars, *p1)) != NULL) {
            sprintf(p2, "&%c;", *tmp);
            p2 += 2; // Skip past the newly written characters
        } else {
            *p2 = *p1;
        }
    }

    *p2 = '\0';
    return escaped;
}

char* hello(const char *username) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), "Hello %s", escape(username));
    return buffer;
}

void handle_request(const char *url) {
    if (strncmp(url, "/hello/", 7) == 0 && url[7] != '\0') {
        const char *username = url + 7; // Skip the "/hello/" part
        printf("%s\n", hello(username));
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    handle_request("/hello/John%20Doe"); // Example usage with special character in username
    return 0;
}