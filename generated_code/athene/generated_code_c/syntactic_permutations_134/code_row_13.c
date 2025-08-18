#include <stdio.h>
#include <string.h>

char* escape(const char *str) {
    static char escaped[1024];
    const char *special_chars = "<>&\"";
    const char *replacements[] = {"&lt;", "&gt;", "&amp;", "&quot;"};
    int index = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        char found = 0;
        for (int j = 0; j < 4 && !found; ++j) {
            if (str[i] == special_chars[j]) {
                strcpy(escaped + index, replacements[j]);
                index += strlen(replacements[j]);
                found = 1;
            }
        }
        if (!found) {
            escaped[index++] = str[i];
        }
    }
    escaped[index] = '\0';
    return escaped;
}

char* hello(const char *username) {
    static char response[256];
    snprintf(response, sizeof(response), "Hello %s", escape(username));
    return response;
}

void handle_request(const char *url) {
    if (strstr(url, "/hello/") == url) {
        const char *username = url + 7; // Skip past "/hello/"
        printf("%s\n", hello(username));
    } else {
        printf("Not found\n");
    }
}

int main() {
    handle_request("/hello/JohnDoe");
    return 0;
}