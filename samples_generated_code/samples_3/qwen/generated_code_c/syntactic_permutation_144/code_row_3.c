#include <stdio.h>
#include <stdlib.h>

int check_and_unsubscribe_email(const char *email) {
    FILE *fp;
    int found = 0;
    char buffer[256];

    fp = fopen("emails.txt", "r");
    if (fp == NULL) {
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
        if (strcmp(buffer, email) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        return 0;
    }

    int result = system("./unsubscribe.sh");
    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    int result = check_and_unsubscribe_email(argv[1]);
    printf("%d\n", result);
    return 0;
}