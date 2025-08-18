#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 256
#define MAX_TEMPLATE_LENGTH 1024

typedef struct {
    char name[MAX_NAME_LENGTH];
    char template[MAX_TEMPLATE_LENGTH];
} Environment;

char* get_query_param(const char *request, const char *param) {
    static char buffer[MAX_NAME_LENGTH] = {0};
    const char *start = strstr(request, param);
    
    if (start && *(start + strlen(param)) == '=') {
        start += strlen(param) + 1;
        size_t length = strcspn(start, "&");
        
        if (length < MAX_NAME_LENGTH - 1) {
            strncpy(buffer, start, length);
            buffer[length] = '\0';
            return buffer;
        }
    }

    return NULL;
}

char* render_template(const char *template_str, const char *name) {
    static char response[MAX_TEMPLATE_LENGTH * 2];
    
    snprintf(response, sizeof(response), template_str, name);
    return response;
}

char* render_response_from_env(Environment env) {
    const char *request = "GET / HTTP/1.1\r\n"
                          "Host: example.com\r\n"
                          "User-Agent: curl/7.68.0\r\n"
                          "Accept: */*\r\n"
                          "name=JohnDoe&otherparam=value\r\n\r\n";
    
    const char *name_param = get_query_param(request, "name");
    
    if (name_param) {
        return render_template(env.template, name_param);
    }
    
    return "Name parameter not found.";
}

char* home() {
    Environment env;
    strcpy(env.name, "");
    strcpy(env.template, "<html><body>Hello, %s!</body></html>");
    
    return render_response_from_env(env);
}

int main() {
    char *response = home();
    printf("%s\n", response);
    return 0;
}