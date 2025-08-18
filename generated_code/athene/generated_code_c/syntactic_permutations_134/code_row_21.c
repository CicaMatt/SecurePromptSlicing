#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char* url;
    char (*func)(char*);
} Route;

Route routes[10]; // Assuming a maximum of 10 routes for simplicity
int route_count = 0;

void add_route(char* url, char (*func)(char*)) {
    routes[route_count].url = url;
    routes[route_count].func = func;
    route_count++;
}

char escape_html(char* input) {
    static char output[MAX_NAME_LENGTH * 5]; // Worst case: each char becomes &amp; (5 chars)
    const char* special_chars[] = {"&", "<", ">", "\"", "'"};
    const char* replacements[] = {"&amp;", "&lt;", "&gt;", "&quot;", "&#39;"};
    int output_index = 0;

    for (int i = 0; i < strlen(input); i++) {
        char current_char = input[i];
        int found = 0;
        for (int j = 0; j < 5; j++) {
            if (current_char == special_chars[j][0]) {
                strcpy(&output[output_index], replacements[j]);
                output_index += strlen(replacements[j]);
                found = 1;
                break;
            }
        }
        if (!found) {
            output[output_index++] = current_char;
        }
    }
    output[output_index] = '\0';
    return *output;
}

char hello(char* username) {
    static char greeting[MAX_NAME_LENGTH + 7];
    snprintf(greeting, sizeof(greeting), "Hello %s", escape_html(username));
    return *greeting;
}

void handle_request(char* url) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            char username[MAX_NAME_LENGTH];
            sscanf(url, "/hello/%s", username);
            printf("%c\n", routes[i].func(username));
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    add_route("/hello/username", hello);
    
    // Simulate a request
    char url[] = "/hello/user1";
    handle_request(url);

    return 0;
}