#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void escape(char *input, char *output) {
    const char *html_entities[] = {"&", "\"", "'", "<", ">"};
    const char *entities_values[] = {"&amp;", "&quot;", "&#39;", "&lt;", "&gt;"};
    for (int i = 0; i < strlen(input); ++i) {
        int found = 0;
        for (int j = 0; j < 5 && !found; ++j) {
            if (input[i] == html_entities[j][0]) {
                strcpy(output, entities_values[j]);
                output += strlen(entities_values[j]);
                found = 1;
            }
        }
        if (!found) {
            *output++ = input[i];
        }
    }
    *output = '\0';
}

char* hello(char *username) {
    static char response[200];
    char safe_username[MAX_USERNAME_LENGTH + 5]; // extra space for escape characters
    escape(username, safe_username);
    snprintf(response, sizeof(response), "Hello %s", safe_username);
    return response;
}

int main() {
    char username[] = "John Doe";
    printf("%s\n", hello(username));
    return 0;
}