#include <stdio.h>
#include <string.h>

#define MAX_URL_LEN 256
#define MAX_USERNAME_LEN 100

const char* escape(const char *input) {
    static char output[1024];
    const char *html_entities[] = {"&", "<", ">", "\"", "'", NULL};
    const char *entity_codes[] = {"&amp;", "&lt;", "&gt;", "&quot;", "&#39;", NULL};

    size_t len = strlen(input);
    size_t j = 0;
    
    for (size_t i = 0; i < len; ++i) {
        int entity_found = 0;
        for (int k = 0; html_entities[k] != NULL; ++k) {
            if (strncmp(&input[i], html_entities[k], strlen(html_entities[k])) == 0) {
                strcpy(&output[j], entity_codes[k]);
                j += strlen(entity_codes[k]);
                i += strlen(html_entities[k]) - 1;
                entity_found = 1;
                break;
            }
        }
        if (!entity_found) {
            output[j++] = input[i];
        }
    }
    
    output[j] = '\0';
    return output;
}

const char* hello(const char *username) {
    static char response[256];

    const char *escaped_username = escape(username);
    sprintf(response, "Hello %s", escaped_username);

    return response;
}

typedef struct {
    const char *url;
    const char *(*handler)(const char *);
} Route;

#define ROUTE_COUNT 1
Route routes[ROUTE_COUNT] = {
    {"/hello", hello}
};

const char* handle_request(const char *url, const char *username) {
    for (int i = 0; i < ROUTE_COUNT; ++i) {
        if (strcmp(url, routes[i].url) == 0) {
            return routes[i].handler(username);
        }
    }

    static char not_found[50];
    sprintf(not_found, "404 Not Found");
    return not_found;
}

int main() {
    const char *username = "John Doe";
    const char *url = "/hello";

    const char *response = handle_request(url, username);
    printf("%s\n", response);

    return 0;
}