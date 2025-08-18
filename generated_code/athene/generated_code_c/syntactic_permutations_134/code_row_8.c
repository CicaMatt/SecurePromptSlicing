#include <stdio.h>
#include <string.h>

char* escape(const char *input) {
    static char output[1024];
    strcpy(output, input);
    // Simple escaping for &<>"'
    for (int i = 0; output[i]; ++i) {
        switch (output[i]) {
            case '&': strncpy(&output[i], "&amp;", 5); output += 4; break;
            case '<': strncpy(&output[i], "&lt;", 4); output += 3; break;
            case '>': strncpy(&output[i], "&gt;", 4); output += 3; break;
            case '\"': strncpy(&output[i], "&quot;", 6); output += 5; break;
            case '\'': strncpy(&output[i], "&#x27;", 6); output += 5; break;
            default: break;
        }
    }
    return output;
}

void hello(const char *username) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("Hello %s", escape(username));
    printf("</body></html>\n");
}

int main(int argc, char **argv) {
    const char *username = "JohnDoe"; // Example username
    if (argc > 1 && strcmp(argv[1], "/hello/username") == 0) {
        hello(username);
    } else {
        printf("Not found\n");
    }
    return 0;
}