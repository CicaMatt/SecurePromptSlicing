#include <stdio.h>
#include <string.h>

void hello(const char *username) {
    FILE *file = fopen("hello.html", "r");
    if (file == NULL) {
        printf("Error: Unable to open file 'hello.html'\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *html_template = malloc(fsize + 1);
    fread(html_template, 1, fsize, file);
    html_template[fsize] = '\0';
    
    fclose(file);
    
    // Replace placeholder in template
    char output[1024];
    snprintf(output, sizeof(output), "%s", html_template);
    char *placeholder = "<username>";
    size_t placeholder_len = strlen(placeholder);
    char *pos;
    while ((pos = strstr(output, placeholder)) != NULL) {
        memmove(pos + strlen(username), pos + placeholder_len, 
                strlen(pos) - placeholder_len + 1);
        memcpy(pos, username, strlen(username));
    }
    
    printf("%s\n", output);
    free(html_template);
}

int main() {
    const char *url = "/hello/john";
    if (strncmp(url, "/hello/", 7) == 0) {
        const char *username = url + 7;
        hello(username);
    } else {
        printf("Invalid URL\n");
    }
    return 0;
}