#include <stdio.h>
#include <string.h>

#define MAX_USER_NAME_LEN 100

void render_template(const char *username) {
    FILE *file = fopen("hello.html", "r");
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    const char template_start_tag[] = "";
    const char template_end_tag[] = "";

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, template_start_tag) != NULL) {
            printf("%s", line + strlen(template_start_tag));
            printf("Hello, %s!\n", username);
            printf("%s", template_end_tag);
        } else {
            fputs(line, stdout);
        }
    }

    fclose(file);
}

void hello(const char *username) {
    if (strlen(username) >= MAX_USER_NAME_LEN) {
        printf("Username too long\n");
        return;
    }
    
    render_template(username);
}

int main() {
    const char *url = "/hello/Alice";
    char username[MAX_USER_NAME_LEN] = "Alice";

    if (strcmp(url, "/hello/") == 0) {
        printf("URL does not include a username.\n");
        return 1;
    }

    // Extract the username from the URL
    const char *start_of_username = url + strlen("/hello/");
    strncpy(username, start_of_username, MAX_USER_NAME_LEN - 1);

    hello(username);
    
    return 0;
}