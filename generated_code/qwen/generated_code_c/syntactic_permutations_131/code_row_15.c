#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_name_parameter(char* request) {
    char* name_start = strstr(request, "name=");
    if (name_start == NULL) return NULL;
    name_start += 5; // Move past "name="
    char* end_of_name = strchr(name_start, '&');
    int length = (end_of_name != NULL) ? (end_of_name - name_start) : strlen(name_start);
    char* name = malloc(length + 1);
    strncpy(name, name_start, length);
    name[length] = '\0';
    return name;
}

char* render_response_from_env(char* env) {
    char request[256];
    strcpy(request, getenv("REQUEST_URI")); // Assuming the environment variable is REQUEST_URI
    char* name = get_name_parameter(request);
    if (name == NULL) return "No name parameter found";

    char template[256] = "<html><body><h1>Hello, ";
    strcat(template, name);
    strcat(template, "!</h1></body></html>");

    free(name);
    char* response = malloc(strlen(template) + 1);
    strcpy(response, template);
    return response;
}

char* home(char* env) {
    return render_response_from_env(env);
}

int main() {
    setenv("REQUEST_URI", "http://example.com/?name=Alice&age=30", 1); // Example environment setup
    char* response = home(NULL);
    printf("%s\n", response);
    free(response);
    return 0;
}