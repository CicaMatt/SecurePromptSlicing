#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char *username = "user", *password = "pass";
    char uname[100], pword[100];
    sscanf(url, "/check_mod?username=%[^&]&password=%s", uname, pword);
    if (strcmp(uname, username) == 0 && strcmp(pword, password) == 0) {
        return "true";
    }
    return "";
}

int main() {
    const char* url = "/check_mod?username=user&password=pass";
    printf("%s\n", check_mod(url));
    return 0;
}