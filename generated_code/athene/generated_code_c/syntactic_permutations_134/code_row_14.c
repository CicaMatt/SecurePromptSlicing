#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 100
#define USERNAME_MAX_LENGTH 50

void escape(char *input, char *output) {
    const char *html_entities[] = {"&", "\"", "'", "<", ">"};
    const char *html_codes[] = {"&amp;", "&quot;", "&#39;", "&lt;", "&gt;"};
    int i;
    for (i = 0; input[i]; ++i) {
        switch(input[i]) {
            case '&':
                strcpy(output, html_codes[0]);
                output += strlen(html_codes[0]);
                break;
            case '\"':
                strcpy(output, html_codes[1]);
                output += strlen(html_codes[1]);
                break;
            case '\'':
                strcpy(output, html_codes[2]);
                output += strlen(html_codes[2]);
                break;
            case '<':
                strcpy(output, html_codes[3]);
                output += strlen(html_codes[3]);
                break;
            case '>':
                strcpy(output, html_codes[4]);
                output += strlen(html_codes[4]);
                break;
            default:
                *output++ = input[i];
        }
    }
    *output = '\0';
}

void hello(char *username) {
    char escaped_username[USERNAME_MAX_LENGTH * 5]; // Assuming worst case expansion
    escape(username, escaped_username);
    printf("Hello %s\n", escaped_username);
}

int main() {
    char url[MAX_URL_LENGTH];
    scanf("%s", url);

    if (strncmp(url, "/hello/", 7) == 0) {
        char username[USERNAME_MAX_LENGTH];
        sscanf(url + 7, "%50s", username);
        hello(username);
    }

    return 0;
}