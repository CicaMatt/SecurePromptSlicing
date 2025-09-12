#include <stdio.h>
#include <string.h>

void render_template(const char *username) {
    printf("Hello, %s!\n", username);
}

int main() {
    const char *url = "/hello/john";
    
    if (strncmp(url, "/hello/", 7) == 0) {
        char username[256];
        strcpy(username, url + 7); // Extract the username from URL
        render_template(username);
    }

    return 0;
}



<!-- hello.html -->
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


To simulate the template rendering in C, we use a simple function `render_template` that prints out a greeting. The HTML file is provided for reference on how it would display the username if rendered properly by a web framework.