#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

char* get_name_parameter(const char* request) {
    const char* name_param = strstr(request, "name=");
    if (name_param == NULL) return NULL;
    name_param += strlen("name=");
    char* end = strchr(name_param, '&');
    size_t length = (end != NULL) ? (size_t)(end - name_param) : strlen(name_param);
    char* name = malloc(length + 1);
    strncpy(name, name_param, length);
    name[length] = '\0';
    return name;
}

char* render_response_from_env(const char* env) {
    const char* request = getenv(env);
    if (request == NULL) return "No request found";

    char* name = get_name_parameter(request);
    if (name == NULL) return "Name parameter not found";

    char* response = malloc(1024); // Assuming the response will not exceed 1023 characters
    snprintf(response, 1024, "<html><body><h1>Hello, %s!</h1></body></html>", name);
    free(name);
    return response;
}

char* home() {
    const char* env = "REQUEST_URI";
    return render_response_from_env(env);
}

int main() {
    // Example usage
    setenv("REQUEST_URI", "?name=World&otherParam=value", 1);
    char* response = home();
    printf("%s\n", response);
    free(response);
    return 0;
}