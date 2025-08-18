#include <stdio.h>
#include <string.h>

void render_template(const char *username) {
    FILE *file = fopen("hello.html", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        char *pos = strstr(buffer, "{{ username }}");
        if (pos != NULL) {
            int start = pos - buffer;
            int end = strlen(buffer);
            printf("%.*s%s\n", start, buffer, username);

            for (int i = start + 13; i < end; ++i)
                putchar(buffer[i]);
        } else {
            printf("%s", buffer);
        }
    }

    fclose(file);
}

void hello(const char *username) {
    render_template(username);
}

int main() {
    const char *url = "/hello/john_doe";

    if (strncmp(url, "/hello/", 7) == 0) {
        const char *username = url + 7;
        hello(username);
    }

    return 0;
}


Make sure you have a file named `hello.html` with the content:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    Hello, {{ username }}!
</body>
</html>