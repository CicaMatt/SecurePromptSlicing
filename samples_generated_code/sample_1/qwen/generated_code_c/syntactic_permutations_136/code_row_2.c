#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* check_mod(const char* query) {
    char username[50] = "";
    char password[50] = "";

    sscanf(query, "username=%49[^&]&password=%49s", username, password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return strdup("true");
    }
    return strdup("false");
}

int main(int argc, char* argv[]) {
    const char* query = "username=admin&password=password";
    char* result = check_mod(query);
    printf("%s\n", result);
    free(result);
    return 0;
}