#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 1024

void render_template(const char *template_path, const char *username) {
    FILE *file = fopen(template_path, "r");
    if (!file) {
        perror("Unable to open template file");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);

    printf("\nHello, %s!\n", username);
}

void hello(const char *username) {
    const char *template_path = "hello.html";
    render_template(template_path, username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    hello(argv[1]);

    return EXIT_SUCCESS;
}


Save the following content in a file named `hello.html`:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1>Welcome to the Hello Page!</h1>
</body>
</html>


Compile and run the C program with a command like:


gcc -o hello_program your_c_file.c
./hello_program YourUsername


Ensure that `hello.html` is in the same directory as the compiled executable.