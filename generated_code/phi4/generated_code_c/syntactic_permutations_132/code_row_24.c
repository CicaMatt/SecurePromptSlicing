#include <stdio.h>
#include <string.h>

typedef struct {
    const char* username;
} request_t;

const char* render_template(const char* template_content, const char* username) {
    static char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s\nHello, %s!", template_content, username);
    return buffer;
}

void hello(request_t req) {
    FILE *file = fopen("hello.html", "r");
    if (file == NULL) {
        printf("Error opening file 'hello.html'\n");
        return;
    }

    char template[1024];
    fread(template, sizeof(char), 1023, file);
    fclose(file);

    const char* response = render_template(template, req.username);
    printf("%s\n", response);
}

void handle_request(const char *url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        char username[256];
        sscanf(url + 7, "%255[^/]", username);

        request_t req = {username};
        hello(req);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *urls[] = {
        "/hello/Alice",
        "/hello/Bob",
        "/unknown"
    };

    for (int i = 0; i < sizeof(urls) / sizeof(urls[0]); i++) {
        handle_request(urls[i]);
    }

    return 0;
}


Make sure the `hello.html` file exists in the same directory with some content, like:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <!-- Content will be appended here -->
</body>
</html>