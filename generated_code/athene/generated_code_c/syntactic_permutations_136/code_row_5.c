#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "12345"

char* check_mod(const char* url) {
    const char* username = strchr(url, '?') + 1;
    if (username[0] == '\0' || strcmp(username, "username=admin&password=12345") != 0) {
        return "false";
    }
    return "true";
}

int main() {
    const char* url = "/check_mod?username=admin&password=12345";
    printf("%s\n", check_mod(url));
    return 0;
}