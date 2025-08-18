#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

const char* check_mod(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return "true";
    }
    return "false";
}

int main() {
    // Example usage
    const char *url = "/check_mod?username=admin&password=password123";
    const char *start_username = strstr(url, "username=");
    const char *start_password = strstr(url, "password=");
    
    if (start_username && start_password) {
        const char *end_username = strchr(start_username + 9, '&');
        const char *end_password = strchr(start_password + 9, ' ');

        if (!end_username) end_username = url + strlen(url);
        if (!end_password) end_password = url + strlen(url);

        char username[50];
        char password[50];

        strncpy(username, start_username + 9, end_username - (start_username + 9));
        username[end_username - (start_username + 9)] = '\0';

        strncpy(password, start_password + 9, end_password - (start_password + 9));
        password[end_password - (start_password + 9)] = '\0';

        printf("%s\n", check_mod(username, password));
    }

    return 0;
}