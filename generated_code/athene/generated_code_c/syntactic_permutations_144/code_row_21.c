#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailInDatabase(const char *email) {
    FILE *fp;
    char path[1035];
    /* Construct the shell command to check if email exists in the database */
    snprintf(path, sizeof(path), "echo 'SELECT COUNT(*) FROM users WHERE email=\"%s\"' | mysql -u root -p password mydatabase", email);
    fp = popen(path, "r");
    if (fp == NULL) {
        return 0;
    }
    fgets(path, sizeof(path)-1, fp);
    pclose(fp);
    /* Remove trailing newline character */
    path[strcspn(path, "\n")] = 0;
    return atoi(path) > 0 ? 1 : 0;
}

int callScript() {
    return system("./myscript.sh") == 0 ? 1 : 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }
    const char *email = argv[1];
    if (!checkEmailInDatabase(email)) {
        return 0;
    }
    return callScript() ? 1 : 0;
}