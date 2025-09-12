#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *url;
} Decorator;

void send_response(FILE *file) {
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
}

void img(const char *name) {
    FILE *file = fopen(name, "r");
    if (!file) {
        fprintf(stderr, "File not found\n");
        return;
    }

    send_response(file);
    fclose(file);
}

Decorator decorate_img() {
    Decorator decorator = {"/img"};
    printf("Decorator URL: %s\n", decorator.url);

    // Simulating extracting the name parameter from the URL
    char url_path[MAX_PATH] = "/img?name=some_image.png";
    char *name_start = strstr(url_path, "name=");
    
    if (name_start) {
        char *name_param = name_start + 5;
        char *name_end = strchr(name_param, '&');
        
        if (!name_end) {
            name_end = url_path + strlen(url_path);
        }
        
        int name_length = name_end - name_param;
        char image_name[MAX_PATH];
        strncpy(image_name, name_param, name_length);
        image_name[name_length] = '\0';
        
        img(image_name);
    } else {
        fprintf(stderr, "No 'name' parameter in URL\n");
    }

    return decorator;
}

int main() {
    decorate_img();
    return 0;
}