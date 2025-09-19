#include <stdio.h>
#include <string.h>

// Simulating a basic templating engine
void render_template(const char *template_file, const char *username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) {
        printf("Error opening template file.\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        // Replace {{ username }} placeholder with actual username
        const char *placeholder = "{{ username }}";
        size_t ph_len = strlen(placeholder);
        
        if (strncmp(buffer, placeholder, ph_len) == 0 && buffer[ph_len] == ' ') {
            printf("%s%s\n", buffer + ph_len + 1, username); // +2 to skip both '{{' and the space
        } else {
            printf("%s", buffer);
        }
    }

    fclose(file);
}

// Function bound to /hello/<username>
void hello(const char *username) {
    render_template("hello.html", username);
}

int main() {
    const char *url = "/hello/Alice";  // Example URL
    if (strncmp(url, "/hello/", 7) == 0) {
        const char *username = url + 7; // Extract username from the URL
        hello(username);                // Call the function bound to this URL
    }

    return 0;
}


Ensure that `hello.html` contains a placeholder `{{ username }}`, like so:
