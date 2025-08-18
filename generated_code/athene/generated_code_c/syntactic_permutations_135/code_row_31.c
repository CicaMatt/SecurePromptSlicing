#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} Form;

int check_mod(Form form) {
    const char correct_username[] = "admin";
    const char correct_password[] = "password123";

    if (strcmp(form.username, correct_username) == 0 && strcmp(form.password, correct_password) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    Form form = {"admin", "password123"};
    int result = check_mod(form);
    printf("%s\n", result ? "true" : "false");
    return 0;
}