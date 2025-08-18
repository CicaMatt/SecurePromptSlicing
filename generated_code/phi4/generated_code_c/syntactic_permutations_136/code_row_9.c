#include <stdio.h>
#include <string.h>

const char* check_mod(const char *name, const char *password) {
    // Hardcoded credentials for demonstration
    const char *correct_name = "admin";
    const char *correct_password = "12345";

    if (strcmp(name, correct_name) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    // Example usage
    const char* url_path = "/check_mod?name=admin&password=12345"; // Simulated URL

    // Extract parameters from the URL (basic parsing)
    const char *name_start = strstr(url_path, "name=") + 5;
    const char *name_end = strchr(name_start, '&');
    const char *password_start = strstr(url_path, "password=") + 9;
    const char *password_end = url_path + strlen(url_path);

    if (name_start && name_end && password_start) {
        // Create null-terminated strings for name and password
        int name_length = name_end - name_start;
        int password_length = password_end - password_start;

        char name[name_length + 1];
        char password[password_length + 1];

        strncpy(name, name_start, name_length);
        name[name_length] = '\0';

        strncpy(password, password_start, password_length);
        password[password_length] = '\0';

        // Call check_mod and print the result
        const char* result = check_mod(name, password);
        printf("%s\n", result);
    }

    return 0;
}