#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* url;
    char* (*func)(char*);
} Route;

Route routes[10];
int route_count = 0;

void add_route(const char* url, char* (*func)(char*)) {
    if (route_count < 10) {
        routes[route_count].url = strdup(url);
        routes[route_count].func = func;
        route_count++;
    }
}

char* escape_html(const char* input) {
    static char output[256];
    const char *html_escapes[] = {"&amp;", "&lt;", "&gt;", "&quot;"};
    const char *special_chars[] = {"&", "<", ">", "\""};
    int j = 0;
    for (int i = 0; input[i]; ++i) {
        int found = 0;
        for (int k = 0; k < 4; ++k) {
            if (input[i] == special_chars[k][0]) {
                strcpy(output + j, html_escapes[k]);
                j += strlen(html_escapes[k]);
                found = 1;
                break;
            }
        }
        if (!found) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
    return output;
}

char* hello(char* username) {
    char buffer[256];
    sprintf(buffer, "Hello %s", escape_html(username));
    return strdup(buffer);
}

void handle_request(const char* url_path) {
    for (int i = 0; i < route_count; ++i) {
        if (strstr(url_path, routes[i].url)) {
            const char* username = url_path + strlen(routes[i].url);
            char* result = routes[i].func(username);
            printf("%s\n", result);
            free(result);
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    add_route("/hello/", hello);
    handle_request("/hello/username");
    return 0;
}