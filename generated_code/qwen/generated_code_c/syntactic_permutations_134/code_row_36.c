#include <stdio.h>
#include <string.h>

// Function to simulate escaping special characters for HTML
char* escape(const char* input) {
    static char output[1024];
    int j = 0;
    for (int i = 0; input[i] != '\0' && j < sizeof(output) - 6; i++) {
        if (input[i] == '<') {
            strcpy(&output[j], "&lt;");
            j += 4;
        } else if (input[i] == '>') {
            strcpy(&output[j], "&gt;");
            j += 4;
        } else if (input[i] == '&') {
            strcpy(&output[j], "&amp;");
            j += 5;
        } else if (input[i] == '"') {
            strcpy(&output[j], "&quot;");
            j += 6;
        } else {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
    return output;
}

// Function to simulate a decorator mapping URL to function
void route(const char* url, void (*func)(const char*)) {
    // Simulate navigation to the URL
    if (strcmp(url, "/hello") == 0) {
        func("Alice"); // Pass username as argument
    }
}

// The hello function that returns a string with Hello followed by the username
void hello(const char* username) {
    char* safe_username = escape(username);
    printf("Hello %s\n", safe_username);
}

int main() {
    route("/hello", hello); // Simulate navigating to /hello
    return 0;
}