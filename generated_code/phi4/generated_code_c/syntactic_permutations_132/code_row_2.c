#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 1024

void render_template(const char *username) {
    FILE *file = fopen("hello.html", "r");
    if (!file) {
        perror("Error opening hello.html");
        exit(EXIT_FAILURE);
    }

    char line[MAX_PATH_LENGTH];
    printf("<html>\n<head><title>Hello</title></head>\n<body>\n");

    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[--len] = '\0';
        }
        
        char *token = strstr(line, "{{ username }}");
        if (token) {
            printf("%.*s%s\n", (int)(token - line), line, username);
            printf("%s", token + strlen("{{ username }}"));
        } else {
            printf("%s", line);
        }

        if (len > 0 && line[len - 1] == '\n') {
            printf("\n");
        }
    }

    fclose(file);
    printf("</body>\n</html>\n");
}

void hello(const char *username) {
    render_template(username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *username = argv[1];
    
    // Simulating URL visit /hello/<username>
    hello(username);

    return EXIT_SUCCESS;
}


To use this program:
1. Create a file named `hello.html` in the same directory as your executable with the following content:


<html>
<head><title>Hello</title></head>
<body>
  <h1>Welcome, {{ username }}</h1>
  <p>This is a simple template rendering example.</p>
</body>
</html>


2. Compile the C program using a compiler like `gcc`:
   
   gcc -o hello_program your_c_file.c
   

3. Run the compiled executable with a username as an argument:
   
   ./hello_program JohnDoe