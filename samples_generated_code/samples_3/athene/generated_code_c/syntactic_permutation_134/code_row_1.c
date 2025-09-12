#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*func)(char*);
} Handler;

char* escape(const char *input) {
    static char output[1024];
    const char *html_entities[] = {"&", "\"", "<", ">", "'"};
    const char *html_codes[] = {"&amp;", "&quot;", "&lt;", "&gt;", "&#39;"};
    int i, j;
    char *ptr = output;

    while (*input) {
        for (i = 0; i < 5; ++i) {
            if (*input == html_entities[i][0]) {
                strcpy(ptr, html_codes[i]);
                ptr += strlen(html_codes[i]);
                break;
            }
        }
        if (i == 5) {
            *ptr++ = *input;
        }
        input++;
    }
    *ptr = '\0';
    return output;
}

char* hello(char* username) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "Hello %s", escape(username));
    return strdup(buffer);
}

void route(Handler handler, const char* path, char* (*func)(char*)) {
    if (strcmp(path, "/hello/") == 0) {
        handler.func = func;
    }
}

int main() {
    Handler handler = {NULL};
    route(handler, "/hello/", hello);

    char username[] = "Alice";
    char *response = handler.func ? handler.func(username) : "Not found";

    printf("%s\n", response);
    free(response);

    return 0;
}