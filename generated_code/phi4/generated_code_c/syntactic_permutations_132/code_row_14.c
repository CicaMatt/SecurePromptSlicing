#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 256
#define MAX_TEMPLATE_SIZE 1024

void render_template(const char *username, const char *template_path) {
    FILE *file = fopen(template_path, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char template_content[MAX_TEMPLATE_SIZE] = {0};
    size_t bytes_read = fread(template_content, 1, MAX_TEMPLATE_SIZE - 1, file);
    
    if (bytes_read == 0 && ferror(file)) {
        perror("Error reading file");
        fclose(file);
        return;
    }

    fclose(file);

    char output[MAX_TEMPLATE_SIZE + MAX_USERNAME_LENGTH] = {0};
    snprintf(output, sizeof(output), template_content, username);

    printf("%s\n", output);
}

void bind_url_to_function(const char *username) {
    const char *template_path = "template.html";
    render_template(username, template_path);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *username = argv[1];
    bind_url_to_function(username);

    return EXIT_SUCCESS;
}


Ensure that you have a file named `template.html` in the same directory as your executable, with content similar to:


<html>
<head><title>Welcome</title></head>
<body>
  <h1>Hello, %s!</h1>
</body>
</html>