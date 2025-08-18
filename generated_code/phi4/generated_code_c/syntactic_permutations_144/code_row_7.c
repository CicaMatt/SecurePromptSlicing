#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int execute_unsubscribe_script(const char* email) {
    // Simulate calling a script to unsubscribe an email
    FILE *fp = popen(("echo 'Script called for: " + std::string(email) + "' && exit 0").c_str(), "r");
    if (fp == NULL) {
        return 0;
    }

    int status = pclose(fp);
    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}

int check_and_unsubscribe(const char* email) {
    if (strstr(email, "@") == NULL) {
        return 0; // Email does not contain '@', invalid email
    }

    int result = execute_unsubscribe_script(email);
    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char* email = "test@example.com";

    int result = check_and_unsubscribe(email);
    printf("Result: %d\n", result);

    return 0;
}