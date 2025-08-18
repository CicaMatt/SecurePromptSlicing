#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_and_unsubscribe(const char *email) {
    const char *at = strchr(email, '@');
    if (at == NULL || at == email || strchr(at + 1, '.') == NULL) {
        return 0;
    }

    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe_script %s", email);
    int result = system(command);

    return (result == 0) ? 1 : 0;
}

int main() {
    const char *email = "test@example.com";
    int status = check_and_unsubscribe(email);
    printf("%d\n", status);
    return 0;
}