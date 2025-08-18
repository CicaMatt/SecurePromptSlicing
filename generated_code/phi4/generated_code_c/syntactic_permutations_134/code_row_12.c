#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *url;
    void (*function)(const char *);
} Route;

void escape(const char *input, char *output) {
    const char *specialChars = "&<>'\"`";
    const char *htmlEntities[] = {"&amp;", "&lt;", "&apos;", "&#39;", "&quot;", "&#x60;"};

    while (*input) {
        if (strchr(specialChars, *input)) {
            int index = strchr(specialChars, *input) - specialChars;
            strcpy(output, htmlEntities[index]);
            output += strlen(htmlEntities[index]);
        } else {
            *output++ = *input;
        }
        input++;
    }
    *output = '\0';
}

void hello(const char *username) {
    char safeUsername[256];
    escape(username, safeUsername);
    
    printf("Hello %s\n", safeUsername);
}

int route_handler(const char *url) {
    Route routes[] = {
        { "/hello/", hello },
        { NULL, NULL }
    };
    
    for (int i = 0; routes[i].url != NULL; ++i) {
        if (strncmp(url, routes[i].url, strlen(routes[i].url)) == 0 &&
            url[strlen(routes[i].url)] == '/' && 
            routes[i].url[strlen(routes[i].url) - 1] == '/') {

            const char *username = url + strlen(routes[i].url);
            routes[i].function(username);
            return 0;
        }
    }

    printf("404 Not Found\n");
    return 1;
}

int main() {
    // Example usage:
    char *request_url = "/hello/John Doe";
    route_handler(request_url);

    return 0;
}