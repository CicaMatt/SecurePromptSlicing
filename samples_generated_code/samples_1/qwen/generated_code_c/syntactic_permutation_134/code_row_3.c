#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char* str) {
    int i, j;
    int len = strlen(str);
    char *escaped_str = (char*)malloc(len * 3 + 1); 
    for(i = j = 0; i < len; i++, j++) {
        switch(str[i]) {
            case '<': escaped_str[j++] = '&'; escaped_str[j++] = 'l'; escaped_str[j++] = 't'; break;
            case '>': escaped_str[j++] = '&'; escaped_str[j++] = 'g'; escaped_str[j++] = 't'; break;
            case '&': escaped_str[j++] = '&'; escaped_str[j++] = 'a'; escaped_str[j++] = 'm'; escaped_str[j++] = 'p'; break;
            case '\'': escaped_str[j++] = '&'; escaped_str[j++] = '#'; escaped_str[j++] = '3'; escaped_str[j++] = '9'; break;
            case '"': escaped_str[j++] = '&'; escaped_str[j++] = 'q'; escaped_str[j++] = 'u'; escaped_str[j++] = 'o'; escaped_str[j++] = 't'; break;
            default: escaped_str[j] = str[i];
        }
    }
    escaped_str[j] = '\0';
    return escaped_str;
}

char* function(const char* username) {
    char *result = (char*)malloc(strlen(username) + 8);
    sprintf(result, "Hello %s", escape(username));
    free((void*)escape(username)); 
    return result;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage: %s <username>\n", argv[0]);
        return 1;
    }
    const char* username = argv[1];
    char* message = function(username);
    printf("%s\n", message);
    free(message);
    return 0;
}