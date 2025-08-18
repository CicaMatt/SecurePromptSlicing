#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **headers;
    size_t num_headers;
} Request;

typedef struct {
    char *body;
    size_t body_len;
    char **headers;
    size_t num_headers;
} Response;

typedef struct {
    Request request;
    Response response;
} Environment;

Response render_response_from_env(Environment env) {
    Response res = {0};
    
    // Get the name parameter from the request
    const char *name_param = "name=John Doe";  // Simulated as if extracted from environment
    
    char template[256] = "<html><body>Hello, %s!</body></html>";
    char rendered_template[512];
    
    // Extract name value from name parameter (assuming it's in the format "name=value")
    char *name_value = strstr(name_param, "=") + 1;
    
    // Render with the name parameter
    snprintf(rendered_template, sizeof(rendered_template), template, name_value);
    
    // Set up response body
    res.body = strdup(rendered_template);
    res.body_len = strlen(res.body);

    // Simulate a header for content type
    const char *headers[] = {"Content-Type: text/html"};
    size_t num_headers = sizeof(headers) / sizeof(headers[0]);
    
    res.headers = malloc(num_headers * sizeof(char *));
    for (size_t i = 0; i < num_headers; ++i) {
        res.headers[i] = strdup(headers[i]);
    }
    res.num_headers = num_headers;

    return res;
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    // Simulated environment setup
    char *headers[] = {"Header1: Value1", "Header2: Value2"};
    Request req = {headers, 2};
    
    Response resp = {0};
    Environment env = {{req}, {resp}};
    
    // Call the home function
    Response response_from_home = home(env);
    
    // Print the response body
    printf("%s\n", response_from_home.body);

    // Clean up dynamically allocated memory
    free(response_from_home.body);
    for (size_t i = 0; i < response_from_home.num_headers; ++i) {
        free(response_from_home.headers[i]);
    }
    free(response_from_home.headers);

    return 0;
}