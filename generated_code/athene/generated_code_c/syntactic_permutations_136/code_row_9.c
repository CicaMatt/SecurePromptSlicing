#include <stdio.h>
#include <string.h>

int check_credentials(const char *name, const char *password) {
    const char *correct_name = "admin";
    const char *correct_password = "123456";
    return (strcmp(name, correct_name) == 0 && strcmp(password, correct_password) == 0);
}

const char* check_mod(const char *url) {
    char name[100];
    char password[100];
    
    sscanf(url, "/check_mod?name=%[^&]&password=%s", name, password);
    
    if (check_credentials(name, password)) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    const char *url = "/check_mod?name=admin&password=123456";
    printf("%s\n", check_mod(url));
    return 0;
}