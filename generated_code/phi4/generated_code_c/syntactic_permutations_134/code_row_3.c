#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *input) {
    static char output[1024];
    const char *special_chars = "<>&\"";
    char *p_output = output;
    
    while (*input != '\0') {
        if (strchr(special_chars, *input)) {
            switch (*input) {
                case '<': strcpy(p_output, "&lt;"); break;
                case '>': strcpy(p_output, "&gt;"); break;
                case '&': strcpy(p_output, "&amp;"); break;
                case '"': strcpy(p_output, "&quot;"); break;
            }
            p_output += strlen(p_output);
        } else {
            *p_output++ = *input;
        }
        input++;
    }
    
    *p_output = '\0';
    return output;
}

char* hello(const char *username) {
    static char response[1024];
    sprintf(response, "Hello %s", escape(username));
    return response;
}

void handle_request(const char *url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        const char *username = url + 7;
        printf("%s\n", hello(username));
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *urls[] = {"/hello/Alice", "/hello/Bob<3", "/unknown"};
    
    for (int i = 0; i < 3; ++i) {
        handle_request(urls[i]);
    }

    return 0;
}