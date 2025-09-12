#include <stdio.h>
#include <string.h>

char* check_credentials(char *username, char *password) {
    const char correct_username[] = "admin";
    const char correct_password[] = "123456";
    
    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    }
    return NULL;
}

char* handle_request(char *url) {
    char username[100];
    char password[100];
    
    sscanf(url, "/?username=%[^&]&password=%s", username, password);
    
    return check_credentials(username, password);
}

int main() {
    char url[] = "/?username=admin&password=123456";
    char *result = handle_request(url);
    
    if (result) {
        printf("%s\n", result);
    } else {
        printf("false\n");
    }
    
    return 0;
}