#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256
#define MAX_USERNAME_LENGTH 50

typedef struct {
    char *username;
} HttpRequest;

typedef struct {
    const char *template_content;
} HttpResponse;

HttpResponse render_template(const char *template_path, const char *username) {
    char buffer[512];
    FILE *file = fopen(template_path, "r");
    if (!file) {
        perror("Failed to open template file");
        exit(EXIT_FAILURE);
    }

    fread(buffer, sizeof(char), sizeof(buffer) - 1, file);
    fclose(file);

    char rendered_content[1024];
    snprintf(rendered_content, sizeof(rendered_content), "%s", buffer);
    size_t username_len = strlen(username);
    strncat(rendered_content, "\n<p>Hello, ", sizeof(rendered_content) - strlen(rendered_content) - 1);
    strncat(rendered_content, username, sizeof(rendered_content) - strlen(rendered_content) - 1);
    strcat(rendered_content, "!</p>");

    return (HttpResponse){.template_content = rendered_content};
}

void handle_request(HttpRequest *request, HttpResponse *response) {
    if (strcmp(request->username, "") != 0) {
        *response = render_template("hello.html", request->username);
    } else {
        response->template_content = "<html><body><h1>Error: No username provided</h1></body></html>";
    }
}

void simulate_http_server() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL (e.g., /hello/johndoe): ");
    fgets(url, sizeof(url), stdin);

    HttpRequest request = {0};
    HttpResponse response = {0};

    if (strncmp(url, "/hello/", 7) == 0) {
        char *username_start = url + 7;
        char *newline_pos = strchr(username_start, '\n');
        if (newline_pos) {
            *newline_pos = '\0';
        }
        strncpy(request.username, username_start, MAX_USERNAME_LENGTH - 1);
    } else {
        printf("Invalid URL format. Only /hello/<username> is supported.\n");
        return;
    }

    handle_request(&request, &response);

    printf("\n%s\n", response.template_content);
}

int main() {
    simulate_http_server();
    return 0;
}



<!-- hello.html -->
<html>
<head><title>Hello</title></head>
<body>
<h1>Welcome!</h1>
<p>Static content goes here.</p>
</body>
</html>


To run the C program, ensure you have a file named `hello.html` in the same directory as your executable. This code simulates handling an HTTP request and rendering a template based on a username extracted from the URL path `/hello/<username>`.