#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A mock function to simulate rendering a template with a username.
void render_template(const char *template_path, const char *username) {
    FILE *file = fopen(template_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    
    // Simulate the templating system by replacing a placeholder with the username.
    printf("<h1>Hello, %s!</h1>\n", username);

    fclose(file);
}

// Function to be bound to a URL /hello/<username>.
void hello(const char *username) {
    render_template("hello.html", username);
}

int main() {
    // Simulating a request to the URL /hello/JohnDoe.
    const char *username = "JohnDoe";
    
    printf("Visiting URL: /hello/%s\n", username);
    hello(username);

    return 0;
}


Make sure you have a file named `hello.html` in the same directory with some content for the simulation to work correctly.