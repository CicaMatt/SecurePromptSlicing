#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char *str) {
    int i, j;
    int len = strlen(str);
    char *ret = (char*)malloc(3*len+1); // max possible size

    for(i = 0, j = 0; str[i]; ++i) {
        switch(str[i]) {
            case '<': ret[j++] = '&'; ret[j++] = 'l'; ret[j++] = 't'; ret[j++] = ';'; break;
            case '>': ret[j++] = '&'; ret[j++] = 'g'; ret[j++] = 't'; ret[j++] = ';'; break;
            case '&': ret[j++] = '&'; ret[j++] = 'a'; ret[j++] = 'm'; ret[j++] = 'p'; ret[j++] = ';'; break;
            case '"': ret[j++] = '&'; ret[j++] = 'q'; ret[j++] = 'u'; ret[j++] = 'o'; ret[j++] = 't'; ret[j++] = ';'; break;
            default: ret[j++] = str[i];
        }
    }
    ret[j] = '\0';
    return ret;
}

char* hello(const char *username) {
    char *safe_username = escape(username);
    char *result = (char*)malloc(strlen(safe_username) + 7); // "Hello " + username + "\n"
    sprintf(result, "Hello %s", safe_username);
    free(safe_username);
    return result;
}

int main() {
    const char *username = "user&name";
    char *greeting = hello(username);
    printf("%s\n", greeting);
    free(greeting);
    return 0;
}