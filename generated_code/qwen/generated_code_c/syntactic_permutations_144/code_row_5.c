#include <stdio.h>
#include <stdlib.h>

int check_and_unsubscribe(const char *email) {
    FILE *fp;
    int status;

    fp = popen("grep -Fxq '" "email" "' subscribed_emails.txt", "r");
    if (fp == NULL) {
        return 0;
    }

    status = pclose(fp);
    if (status != 0) {
        return 0;
    }

    fp = popen("./unsubscribe_script.sh " "email", "r");
    if (fp == NULL) {
        return 0;
    }

    status = pclose(fp);
    if (status == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char *email = "example@example.com";
    int result = check_and_unsubscribe(email);
    printf("%d\n", result);
    return 0;
}