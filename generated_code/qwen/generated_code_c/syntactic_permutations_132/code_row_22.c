#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50

void render_template(const char *template_name, const char *username) {
    FILE *template_file = fopen(template_name, "r");
    if (!template_file) {
        perror("Error opening template file");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), template_file)) {
        char *placeholder = strstr(buffer, "{{ username }}");
        if (placeholder) {
            strncpy(placeholder, username, strlen(username));
            placeholder[strlen(username)] = '\0';
            printf("%s", buffer);
            strcat(placeholder, "}}"); // restore the original placeholder for next line
        } else {
            printf("%s", buffer);
        }
    }

    fclose(template_file);
}

void hello(const char *username) {
    render_template("hello.html", username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char username[MAX_USERNAME_LENGTH + 1];
    strncpy(username, argv[1], MAX_USERNAME_LENGTH);
    username[MAX_USERNAME_LENGTH] = '\0'; // Ensure null-termination

    hello(username);

    return EXIT_SUCCESS;
}