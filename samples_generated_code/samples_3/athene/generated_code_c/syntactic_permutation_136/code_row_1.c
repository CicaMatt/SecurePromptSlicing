#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char* username = "correct_user";
    const char* password = "correct_pass";

    const char* user_start = "&user=";
    const char* pass_start = "&pass=";
    int user_pos = strstr(url, user_start) - url + strlen(user_start);
    int pass_pos = strstr(url, pass_start) - url + strlen(pass_start);

    if (user_pos > 0 && pass_pos > 0) {
        char extracted_user[100];
        char extracted_pass[100];

        int i;
        for (i = 0; url[user_pos + i] != '&' && url[user_pos + i] != '\0'; ++i) {
            extracted_user[i] = url[user_pos + i];
        }
        extracted_user[i] = '\0';

        int j;
        for (j = 0; url[pass_pos + j] != '&' && url[pass_pos + j] != '\0'; ++j) {
            extracted_pass[j] = url[pass_pos + j];
        }
        extracted_pass[j] = '\0';

        if (strcmp(extracted_user, username) == 0 && strcmp(extracted_pass, password) == 0) {
            return "true";
        }
    }

    return "";
}

int main() {
    const char* url = "http://example.com/check_mod?someparam=value&user=correct_user&pass=correct_pass";
    printf("%s\n", check_mod(url));
    return 0;
}