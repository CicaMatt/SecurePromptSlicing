#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

typedef struct {
    char url[MAX_URL_LENGTH];
    void (*func)(char *);
} Route;

void hello(char *username) {
    printf("Hello %s\n", username);
}

char* escape(char *input) {
    static char output[512];
    const char specialChars[] = {'&', '<', '>', '"', '\''};
    const char replacements[][4] = {"&amp;", "&lt;", "&gt;", "&quot;", "&#39;"};

    size_t i, j, k;
    for (i = 0; input[i] != '\0';) {
        int replaced = 0;

        for (j = 0; j < sizeof(specialChars)/sizeof(specialChars[0]); ++j) {
            if (input[i] == specialChars[j]) {
                strcpy(&output[k], replacements[j]);
                k += strlen(replacements[j]);
                i++;
                replaced = 1;
                break;
            }
        }

        if (!replaced) {
            output[k++] = input[i++];
        }
    }

    output[k] = '\0';
    return output;
}

void handle_request(char *request_url, Route routes[], int num_routes) {
    char *token;
    token = strtok(request_url, "/");

    for (int i = 0; i < num_routes; ++i) {
        if (strcmp(token, "hello") == 0 && strcmp(token = strtok(NULL, "/"), "") != 0) {
            routes[i].func(escape(token));
            return;
        }
    }

    printf("404 Not Found\n");
}

int main() {
    Route routes[] = {{"hello", hello}};
    int num_routes = sizeof(routes) / sizeof(routes[0]);

    char request_url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    fgets(request_url, MAX_URL_LENGTH, stdin);
    request_url[strcspn(request_url, "\n")] = '\0'; // Remove newline

    handle_request(request_url, routes, num_routes);

    return 0;
}