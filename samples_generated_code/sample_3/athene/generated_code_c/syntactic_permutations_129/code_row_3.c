#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment *env) {
    const char *name = "World"; // Default name if not found
    const char *query = getenv("QUERY_STRING");
    if (query != NULL && strstr(query, "name=") == query) {
        name = query + 5;
        if ((char *)strchr(name, '&')) *(char *)strchr(name, '&') = '\0';
    }
    
    const char *template = env->name; // Assuming environment holds the template
    char rendered[256];
    snprintf(rendered, sizeof(rendered), "Hello, %s! This is your personalized message: '%s'", name, template);
    Response response = {.content = strdup(rendered)};
    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}