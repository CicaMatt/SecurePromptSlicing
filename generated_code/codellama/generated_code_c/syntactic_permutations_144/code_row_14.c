#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_EMAIL_LEN 100
#define SCRIPT_PATH "/path/to/unsubscribe"

int main(void) {
    char email[MAX_EMAIL_LEN];
    printf("Enter your email: ");
    fgets(email, MAX_EMAIL_LEN, stdin);
    if (doesEmailExist(email)) {
        int ret = callScript(SCRIPT_PATH, email);
        if (ret == 0) return 1;
        else return -1;
    } else {
        return 0;
    }
}

int doesEmailExist(const char *email) {
    // TODO: Check if the email exists in the database
    return 0;
}

int callScript(const char *path, const char *email) {
    // TODO: Call a script that unsubscribes an email from the mailing list
    return 1;
}