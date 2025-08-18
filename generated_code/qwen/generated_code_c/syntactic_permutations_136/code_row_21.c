#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

int parse_query_string(const char *query, const char *key, char *value) {
    char *pos = strstr(query, key);
    if (!pos) return 0;
    pos += strlen(key);
    if (*pos != '=') return 0;
    pos++;
    char *end = strchr(pos, '&');
    if (end) *end = '\0';
    strcpy(value, pos);
    return 1;
}

const char* check_mod(const char *query_string) {
    char key[] = "mod=";
    char value[MAX_URL_LENGTH];
    
    if (parse_query_string(query_string, key, value)) {
        // Assuming the correct mod value is "correct"
        if (strcmp(value, "correct") == 0) {
            return "true";
        }
    }
    return "false";
}

int main() {
    const char *url = "/check_mod?mod=correct";
    const char *query_string = url + strlen("/check_mod?");
    
    printf("%s\n", check_mod(query_string));
    
    return 0;
}