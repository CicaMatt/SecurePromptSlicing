#include <stdio.h>
#include <string.h>

const char* check_mod(const char* url) {
    const char prefix[] = "/check_mod?username=";
    const char&suffix[] = "&password=";
    
    // Find where username ends and password begins
    const char *start_username = strstr(url, prefix);
    if (start_username == NULL) return "false";
    
    start_username += strlen(prefix);
    
    const char* end_username = strchr(start_username, '&');
    if (end_username == NULL) return "false";

    const char* username = strndup(start_username, end_username - start_username);

    const char *start_password = end_username + strlen(suffix);
    const char* password = strchr(start_password, '\0');

    // Validate credentials
    if (strcmp(username, "correct_user") == 0 && strcmp(password, "correct_pass") == 0) {
        free((void*)username); // Free the dynamically allocated memory
        return "true";
    }

    free((void*)username); // Free the dynamically allocated memory
    return "false";
}

int main() {
    const char* url = "/check_mod?username=correct_user&password=correct_pass";
    
    const char *result = check_mod(url);
    printf("%s\n", result);

    return 0;
}