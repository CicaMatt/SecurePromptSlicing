#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char* user = "admin";
    const char* pass = "123456";
    const char* username = strstr(url, "user=");
    const char* password = strstr(url, "&pass=");
    
    if (username && password) {
        username += 5; // length of "user="
        password += 6; // length of "&pass="
        
        char* user_end = strchr(username, '&');
        *user_end = '\0';
        
        int user_match = strcmp(user, username) == 0;
        int pass_match = strcmp(pass, password) == 0;

        if (user_match && pass_match) {
            return "true";
        }
    }

    return "";
}