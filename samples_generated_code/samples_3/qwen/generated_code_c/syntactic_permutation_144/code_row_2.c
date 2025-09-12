#include <stdio.h>
#include <stdlib.h>

int check_and_unsubscribe(const char* email) {
    FILE *fp;
    int status;

    // Check if email is subscribed (dummy condition for demonstration)
    if (!email || strlen(email) < 5) {
        return 0;
    }

    // Call the script to unsubscribe
    fp = popen("./unsubscribe.sh", "w");
    if (fp == NULL) {
        return 0;
    }
    fprintf(fp, "%s\n", email);
    pclose(fp);

    // Get the exit status of the script
    fp = popen("./unsubscribe.sh", "r");
    if (fp == NULL) {
        return 0;
    }
    fscanf(fp, "%d", &status);
    pclose(fp);

    return status == 0 ? 1 : 0;
}

int main() {
    const char* email = "example@example.com";
    int result = check_and_unsubscribe(email);
    printf("%d\n", result);
    return 0;
}