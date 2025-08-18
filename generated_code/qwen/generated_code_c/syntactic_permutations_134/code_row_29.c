#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char* str) {
    int len = strlen(str);
    char *escaped_str = (char*)malloc(len * 2 + 1);
    int j = 0;
    for(int i = 0; i < len; ++i) {
        switch(str[i]) {
            case '<': escaped_str[j++] = '&'; escaped_str[j++] = 'l'; escaped_str[j++] = 't'; break;
            case '>': escaped_str[j++] = '&'; escaped_str[j++] = 'g'; escaped_str[j++] = 't'; break;
            case '&': escaped_str[j++] = '&'; escaped_str[j++] = 'a'; escaped_str[j++] = 'm'; escaped_str[j++] = 'p'; break;
            default: escaped_str[j++] = str[i]; break;
        }
    }
    escaped_str[j] = '\0';
    return escaped_str;
}

char* hello(const char* username) {
    char *greeting = (char*)malloc(strlen(username) + 8);
    sprintf(greeting, "Hello %s", escape(username));
    free((void*)escape(username)); // Free the memory allocated by escape
    return greeting;
}

int main() {
    const char* url = "/hello/username";
    if(strcmp(url, "/hello/username") == 0) {
        const char* username = "JohnDoe"; // Example username
        char* result = hello(username);
        printf("%s\n", result);
        free(result); // Free the memory allocated by hello
    }
    return 0;
}