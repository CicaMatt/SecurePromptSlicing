#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int regex_match(const char *str, const char *regex) {
    int i = 0, j = 0;
    while (regex[j] != '\0') {
        if (regex[j] == '.' && str[i] == '.') {
            j++;
            i++;
            continue;
        }
        if ((regex[j] >= 'A' && regex[j] <= 'Z') ||
            (regex[j] >= 'a' && regex[j] <= 'z') ||
            (regex[j] >= '0' && regex[j] <= '9') ||
            regex[j] == '-') {
            if ((str[i] >= 'A' && str[i] <= 'Z') ||
                (str[i] >= 'a' && str[i] <= 'z') ||
                (str[i] >= '0' && str[i] <= '9') ||
                str[i] == '-') {
                j++;
                i++;
            } else {
                return 0;
            }
        } else if (regex[j] == '*') {
            j++;
            while ((str[i] >= 'A' && str[i] <= 'Z') ||
                   (str[i] >= 'a' && str[i] <= 'z') ||
                   (str[i] >= '0' && str[i] <= '9') ||
                   str[i] == '-') {
                i++;
            }
        } else {
            return 0;
        }
    }
    return regex[j - 1] == '*' || (regex[j - 1] == '.' && str[i - 1] == '.');
}

void handle_redirect(const char *target) {
    const char *regex = "^[A-Za-z0-9-]+\\.";
    if (regex_match(target, regex)) {
        printf("Redirect to: %s\n", target);
    } else {
        printf("Redirect to: /\n");
    }
}

int main() {
    char query_string[] = "?target=somepage.html";
    const char *start = strchr(query_string, 't');
    if (start) {
        start += 6; // move past "target="
        char *end = strchr(start, '&');
        char target[256];
        if (!end) end = query_string + strlen(query_string);
        strncpy(target, start, end - start);
        target[end - start] = '\0';
        handle_redirect(target);
    }
    return 0;
}