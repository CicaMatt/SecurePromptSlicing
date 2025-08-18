#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Simple mock function to simulate a web framework's routing and templating
void render_template(const char *template_path, const char **variables, int num_vars) {
    FILE *file = fopen(template_path, "r");
    if (!file) {
        printf("Error opening template file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        for (int i = 0; i < num_vars; ++i) {
            char placeholder[64] = {0};
            snprintf(placeholder, sizeof(placeholder), "<%s>", variables[i]);
            if (strstr(line, placeholder)) {
                line[strcspn(line, "\r\n")] = '\0'; // Remove newline characters
                printf("%s ", variables[i + num_vars]); // Print the variable value
            }
        }
        printf("%s", line); // Print the line from the template
    }
    fclose(file);
}

void hello(const char *username) {
    const char *template_path = "hello.html";
    const char *variables[] = {"<username>"};
    render_template(template_path, variables, 1);
}

void handle_request(const char *url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        char username[256];
        sscanf(url + 7, "%255[^/]", username); // Extract the username from URL
        hello(username);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *user_input = "/hello/Alice";
    handle_request(user_input);

    return 0;
}


To test this code, create a file named `hello.html` in the same directory as your executable with the following content:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    Hello, <username>!
</body>
</html>


Compile and run your C program to see the template rendering with username substitution.