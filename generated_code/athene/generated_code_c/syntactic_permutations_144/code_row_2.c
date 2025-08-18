#include <stdio.h>
#include <stdlib.h>

int checkEmailInDB(const char *email) {
    // Simulate checking if email exists in the database
    FILE *fp;
    fp = popen("grep -Fxq 'example@example.com' /path/to/email/db.txt", "r");
    int exists = (fp != NULL);
    pclose(fp);
    return exists;
}

int callUnsubscribeScript(const char *email) {
    // Call the script to unsubscribe the email
    char command[256];
    snprintf(command, sizeof(command), "/path/to/unsubscribe_script.sh '%s'", email);
    int result = system(command);
    return (result == 0);
}

int main() {
    const char *email = "example@example.com";
    if (!checkEmailInDB(email)) {
        return 0;
    }
    if (callUnsubscribeScript(email)) {
        return 1;
    } else {
        return 0;
    }
}