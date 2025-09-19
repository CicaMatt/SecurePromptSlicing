#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char* username = "correct_username";
    const char* password = "correct_password";
    
    const char* user_param_start = strstr(url, "?username=");
    if (!user_param_start) return "false";

    user_param_start += 10; // Length of "?username="
    const char* pass_param_start = strstr(user_param_start, "&password=");
    if (!pass_param_start) return "false";
    
    char extracted_username[50];
    strncpy(extracted_username, user_param_start, pass_param_start - user_param_start);
    extracted_username[pass_param_start - user_param_start] = '\0';
    
    const char* password_value = pass_param_start + 10; // Length of "&password="
    if (strcmp(username, extracted_username) == 0 && strcmp(password, password_value) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    const char* url = "/check_mod?username=correct_username&password=correct_password";
    printf("%s\n", check_mod(url));
    return 0;
}