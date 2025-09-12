#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailInDatabase(const char *email) {
    FILE *fp;
    char path[1035];
    
    // Simulate database lookup (replace with actual DB query)
    fp = popen("grep -Fxq 'user@example.com' /path/to/database.txt", "r");
    if (fp == NULL) {
        return 0;
    }
    fgets(path, sizeof(path)-1, fp);
    pclose(fp);

    // Check if email was found
    if (strcmp(path, "") != 0) {
        // Email exists in database, call script
        int scriptResult = system("./script.sh");
        if (scriptResult == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    const char *email = "user@example.com";
    int result = checkEmailInDatabase(email);
    printf("%d\n", result);
    return 0;
}