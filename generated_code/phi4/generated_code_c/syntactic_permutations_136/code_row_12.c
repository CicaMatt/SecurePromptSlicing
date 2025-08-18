#include <stdio.h>
#include <string.h>

// Function to simulate checking a user's credentials
const char* check_credentials(const char *username, const char *password) {
    // Dummy credentials for demonstration purposes
    const char *correct_username = "user123";
    const char *correct_password = "pass456";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    }
    return "false";
}

// Function to simulate getting the username and password from a URL
void get_credentials_from_url(const char *url, char *username, char *password, int max_len) {
    // Simulate extracting credentials from a URL (assuming format "/check_mod?user=<username>&pass=<password>")
    const char *user_start = strstr(url, "user=");
    const char *pass_start = strstr(url, "pass=");

    if (user_start && pass_start) {
        user_start += 5; // Move past 'user='
        pass_start += 5; // Move past 'pass='

        const char *user_end = strchr(user_start, '&');
        const char *pass_end = strchr(pass_start, '&');

        size_t user_len = (user_end) ? strlen(user_start) : strlen(user_start);
        size_t pass_len = (pass_end) ? strlen(pass_start) : strlen(pass_start);

        if (user_len < max_len - 1 && pass_len < max_len - 1) {
            strncpy(username, user_start, user_len);
            username[user_len] = '\0';
            strncpy(password, pass_start, pass_len);
            password[pass_len] = '\0';
        }
    }
}

// Function to be called when the user visits the URL /check_mod
const char* check_mod(const char *url) {
    char username[100];
    char password[100];

    get_credentials_from_url(url, username, password, sizeof(username));

    return check_credentials(username, password);
}

int main() {
    const char *url = "/check_mod?user=user123&pass=pass456";
    printf("Credentials are correct: %s\n", check_mod(url));
    
    const char *invalid_url = "/check_mod?user=wronguser&pass=wrongpass";
    printf("Credentials are correct: %s\n", check_mod(invalid_url));

    return 0;
}