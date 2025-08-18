#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_in_db(const char *email) {
    FILE *fp;
    char path[1035];
    const char *cmd = "grep -Fxq '%s' database.txt";
    
    snprintf(path, sizeof(path), cmd, email);
    fp = popen(path, "r");
    if (fp == NULL) {
        return 0;
    }
    
    // Read the output from grep
    int found = fread(path, 1, 1, fp) != 0;

    pclose(fp);

    return found;
}

int call_script(const char *email) {
    char command[256];
    snprintf(command, sizeof(command), "./script.sh '%s'", email);
    return system(command) == 0 ? 1 : 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    const char *email = argv[1];
    
    if (!check_email_in_db(email)) {
        return 0;
    }

    return call_script(email);
}