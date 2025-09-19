#include <stdio.h>
#include <string.h>

const char* check_mod(const char* url) {
    const char* valid_username = "user";
    const char* valid_password = "pass";

    if (strncmp(url, "username=user&password=pass", strlen("username=user&password=")) == 0) {
        return "true";
    }
    
    return "false";
}

int main() {
    const char* url1 = "username=user&password=pass";
    const char* url2 = "username=admin&password=1234";

    printf("%s\n", check_mod(url1)); // Output: true
    printf("%s\n", check_mod(url2)); // Output: false

    return 0;
}