#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 1024

int check_credentials(const char *username, const char *password) {
    FILE *fp = fopen("login.txt", "r");
    if (!fp) return 0;

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp)) {
        char stored_username[50], stored_password[50];
        if (sscanf(line, "%49[^:]:%49s", stored_username, stored_password) == 2) {
            if (strcmp(stored_username, username) == 0 && strcmp(stored_password, password) == 0) {
                fclose(fp);
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}

int main() {
    char *username = getenv("QUERY_STRING");
    if (!username || strlen(username) < 9 || username[8] != '=') {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Invalid request</body></html>");
        return 1;
    }
    username += 9;

    char *password = strchr(username, '&');
    if (!password) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Invalid request</body></html>");
        return 1;
    }
    *password++ = '\0';

    password += strlen("password=");
    char decoded_username[50], decoded_password[50];
    urldecode(username, decoded_username);
    urldecode(password, decoded_password);

    if (check_credentials(decoded_username, decoded_password)) {
        printf("Location: home.html\n\n");
    } else {
        printf("Location: login.html\n\n");
    }
    return 0;
}

void urldecode(char *src, char *dst) {
    while (*src) {
        if ((*src == '%') &&
            ((src[1] >= '0' && src[1] <= '9') || (src[1] >= 'a' && src[1] <= 'f') ||
             (src[1] >= 'A' && src[1] <= 'F')) &&
            ((src[2] >= '0' && src[2] <= '9') || (src[2] >= 'a' && src[2] <= 'f') ||
             (src[2] >= 'A' && src[2] <= 'F'))) {
            *dst++ = (char)strtol(src + 1, NULL, 16);
            src += 3;
        } else if (*src == '+') {
            *dst++ = ' ';
            src++;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
}