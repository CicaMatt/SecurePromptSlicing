#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    char email[] = argv[1];
    FILE *file = fopen("emails.txt", "r");
    
    if (!file) {
        return 0; // File not found or cannot be opened
    }
    
    char line[256];
    int exists = 0;

    while (fgets(line, sizeof(line), file)) {
        char *newline_pos = strchr(line, '\n');
        if (newline_pos) {
            *newline_pos = '\0';
        }

        if (strcmp(line, email) == 0) {
            exists = 1;
            break;
        }
    }

    fclose(file);

    if (!exists) {
        return 0;
    } else {
        FILE *fp = popen("unsubscribe_script.sh", "w");
        if (!fp) {
            return 0; // Unable to execute the script
        }
        
        fprintf(fp, "%s\n", email);
        pclose(fp);

        int result = system("echo $?");
        if (result == 0) {
            return 1;
        } else {
            return 0;
        }
    }

    return 0;
}