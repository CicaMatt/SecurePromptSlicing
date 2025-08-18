#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 100

char* escape(const char *input) {
    static char output[MAX_USERNAME_LEN * 4]; // worst case expansion
    char *ptr = output;
    for (const char *p = input; *p != '\0'; p++) {
        switch (*p) {
            case '<': strcpy(ptr, "&lt;"); ptr += 4; break;
            case '>': strcpy(ptr, "&gt;"); ptr += 4; break;
            case '&': strcpy(ptr, "&amp;"); ptr += 5; break;
            case '"': strcpy(ptr, "&quot;"); ptr += 6; break;
            default: *ptr++ = *p;
        }
    }
    *ptr = '\0';
    return output;
}

typedef struct {
    const char* url;
    void (*handler)(const char*);
} Route;

void hello(const char* username) {
    printf("Hello %s\n", escape(username));
}

Route routes[] = {
    {"/hello", (void*)hello},
};

void dispatch(const char *url, const char *username) {
    for (int i = 0; i < sizeof(routes)/sizeof(routes[0]); ++i) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler(username);
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    const char *url = "/hello";
    const char *username = "John Doe";
    dispatch(url, username);
    return 0;
}