#include <stdio.h>
#include <stdlib.h>
#include "url_bindings.h"

void hello(char *username) {
    // Get path to template file
    char *template_path = get_template_path("hello.html");

    // Read contents of template file
    FILE *file;
    file = fopen(template_path, "r");

    if (file == NULL) {
        printf("Template file not found\n");
        return;
    }

    char buffer[1024];
    int length = 0;

    // Read template contents into buffer
    while ((length = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        printf("%s", buffer);
    }

    fclose(file);
}