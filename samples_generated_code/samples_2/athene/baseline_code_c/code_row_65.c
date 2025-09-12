#include <stdio.h>
#include <string.h>

char* get_from_url(char *url, const char *param) {
    char *start = strstr(url, param);
    if (start == NULL) return "";
    start += strlen(param);
    char *end = strchr(start, '&');
    if (end == NULL) end = strchr(start, '?');
    if (end == NULL) return start;
    *end = '\0';
    return start;
}

char* check_mod(const char *url) {
    static char result[10];
    char username[50], password[50];
    strcpy(username, get_from_url((char*)url, "username="));
    strcpy(password, get_from_url((char*)url, "password="));

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        strcpy(result, "true");
    } else {
        strcpy(result, "");
    }
    return result;
}

int main() {
    const char *url = "/check_mod?username=admin&password=admin123";
    printf("%s\n", check_mod(url));
    return 0;
}