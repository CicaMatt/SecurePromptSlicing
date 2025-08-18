#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char *str) {
    int i, j;
    int len = strlen(str);
    char *escaped_str = (char *)malloc(len * 2 + 1);

    for(i = j = 0; str[i]; i++) {
        switch(str[i]) {
            case '<': escaped_str[j++] = '&'; escaped_str[j++] = 'l'; escaped_str[j++] = 't'; escaped_str[j++] = ';'; break;
            case '>': escaped_str[j++] = '&'; escaped_str[j++] = 'g'; escaped_str[j++] = 't'; escaped_str[j++] = ';'; break;
            case '&': escaped_str[j++] = '&'; escaped_str[j++] = 'a'; escaped_str[j++] = 'm'; escaped_str[j++] = 'p'; escaped_str[j++] = ';'; break;
            case '\'': escaped_str[j++] = '&'; escaped_str[j++] = '#'; escaped_str[j++] = '3'; escaped_str[j++] = '9'; escaped_str[j++] = ';'; break;
            case '\"': escaped_str[j++] = '&'; escaped_str[j++] = '#'; escaped_str[j++] = '3'; escaped_str[j++] = '4'; escaped_str[j++] = ';'; break;
            default: escaped_str[j++] = str[i];
        }
    }
    escaped_str[j] = '\0';
    return escaped_str;
}

char* hello(const char *username) {
    char *escaped_username = escape(username);
    char *greeting = (char *)malloc(strlen(escaped_username) + 7);
    sprintf(greeting, "Hello %s", escaped_username);
    free(escaped_username);
    return greeting;
}

int main() {
    const char *url_path = "/hello/username";
    const char *username = "user&name<test>";
    
    // Simulating the URL path parsing
    if (strstr(url_path, "/hello/") == url_path) {
        username = url_path + 7; // Assuming no trailing slash in the URL
        char *result = hello(username);
        printf("%s\n", result);
        free(result);
    }
    
    return 0;
}