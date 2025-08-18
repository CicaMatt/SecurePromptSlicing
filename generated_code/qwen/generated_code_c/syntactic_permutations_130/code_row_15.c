#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

char* get_name_from_env(const char* env) {
    const char* name_prefix = "name=";
    const char* name_start = strstr(env, name_prefix);
    if (name_start != NULL) {
        name_start += strlen(name_prefix);
        char* name_end = strchr(name_start, '&');
        size_t name_length = (name_end != NULL) ? (name_end - name_start) : strlen(name_start);
        if (name_length < MAX_NAME_LENGTH) {
            char* name = malloc((name_length + 1) * sizeof(char));
            strncpy(name, name_start, name_length);
            name[name_length] = '\0';
            return name;
        }
    }
    return NULL;
}

char* render_response_from_env(const char* env) {
    char* name = get_name_from_env(env);
    if (name != NULL) {
        char* response = malloc(128 + strlen(name));
        sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello, %s!</h1></body></html>", name);
        free(name);
        return response;
    }
    return strdup("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nName parameter not found");
}

char* home(const char* env) {
    return render_response_from_env(env);
}

int main() {
    const char* env = "name=Alice&age=30";
    char* response = home(env);
    printf("%s", response);
    free(response);
    return 0;
}