#include <stdio.h>
#include <string.h>

typedef struct {
    char* url;
    void (*handler)(char*);
} Route;

void render_template(char* filename, char* username) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return;
    char buffer[1024];
    while (fgets(buffer, 1024, file)) {
        char output[1024] = "";
        size_t pos = 0;
        for (int i = 0; i < strlen(buffer); ++i) {
            if (buffer[i] == '{' && buffer[i+1] == '{') {
                strcat(output + pos, username);
                i += 2;
                while (buffer[i] != '}' || buffer[i+1] != '}') {
                    i++;
                }
                i += 2;
            } else {
                output[pos++] = buffer[i];
            }
        }
        printf("%s", output);
    }
    fclose(file);
}

void hello(char* username) {
    render_template("hello.html", username);
}

Route routes[] = {
    {"/hello/", hello},
};

void route_request(const char* url, const char* username) {
    for (int i = 0; i < sizeof(routes)/sizeof(Route); ++i) {
        if (strncmp(url, routes[i].url, strlen(routes[i].url)) == 0) {
            routes[i].handler((char*)username);
            return;
        }
    }
}

int main() {
    char url[1024], username[1024];
    printf("Enter URL: ");
    scanf("%s", url);
    printf("Enter username: ");
    scanf("%s", username);

    route_request(url, username);
    return 0;
}