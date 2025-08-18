#include <stdio.h>
#include <string.h>

int auth_mod(const char* name, const char* password, const char* session) {
    // Dummy implementation for demonstration purposes
    return strcmp(name, "mod") == 0 && strcmp(password, "secret") == 0 && strcmp(session, "12345") == 0;
}

void check_mod(const char* url) {
    char name[100], password[100], session[100];
    sscanf(url, "/check_mod?name=%[^&]&password=%[^&]&session=%s", name, password, session);
    if (auth_mod(name, password, session)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
}

int main() {
    const char* url = "/check_mod?name=mod&password=secret&session=12345";
    check_mod(url);
    return 0;
}