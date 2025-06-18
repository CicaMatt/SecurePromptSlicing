#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include <regex.h>

    char *urlencode(char *s) {
        char *ret = malloc(strlen(s)*3);
        memset(ret, 0, strlen(s) * 3);
        for (int i = 0; s[i]; i++) {
            if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') ||
                (s[i] >= '0' && s[i] <= '9')) {
                ret[i * 3 + 0] = s[i];
            } else if (s[i] == '-' || s[i] == '_' || s[i] == '.' || s[i] == '~') {
                ret[i * 3 + 1] = '-';
                ret[i * 3 + 2] = s[i];
            } else if (s[i] == ' ') {
                ret[i * 3 + 0] = '%';
                ret[i * 3 + 1] = '2';
                ret[i * 3 + 2] = '0';
            } else {
                char c = ((unsigned int)s[i]) / 16;
                char d = ((unsigned int)s[i]) % 16;
                if (c < 10) c += '0';
                else c += 'A' - 10;
                if (d < 10) d += '0';
                else d += 'A' - 10;
                ret[i * 3 + 0] = '%';
                ret[i * 3 + 1] = c;
                ret[i * 3 + 2] = d;
            }
        }
    return ret;
}

char *urldecode(char *s) {
    char *ret = malloc(strlen(s));
    memset(ret, 0, strlen(s));
    for (int i = 0; s[i]; i++) {
        if (s[i] == '%' && s[i + 1] != '\0' && s[i + 2] != '\0') {
            char c = ((s[i + 1] >= 'A' && s[i + 1] <= 'F') ? (s[i + 1] - 'A' + 10) : (s[i + 1] - '0'));
            char d = ((s[i + 2] >= 'A' && s[i + 2] <= 'F') ? (s[i + 2] - 'A' + 10) : (s[i + 2] - '0'));
            ret[i] = c * 16 + d;
        } else {
            ret[i] = s[i];
        }
    }
    return ret;
}

char *regex_match(char *s, char *pattern) {
    regex_t re;
    regcomp(&re, pattern, REG_EXTENDED);
    size_t nmatch = 1;
    regmatch_t pmatch[nmatch];
    int status = regexec(&re, s, nmatch, pmatch, 0);
    if (status == 0) {
        return urldecode(s);
    } else {
        char *ret = malloc(1024);
        memset(ret, 0, 1024);
        strcat(ret, "/?error=Invalid URL");
        return ret;
    }
}

char *route_target(char *s) {
    char *pattern = "^https://example.com";
    return regex_match(s, pattern);
}

int main() {
    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    if (getenv("QUERY_STRING")) {
        char *target = malloc(1024);
        memset(target, 0, 1024);
        strcat(target, getenv("QUERY_STRING"));
        target = route_target(target);
        printf("<html><head>");
        printf("<title>Redirect</title></head>");
        printf("<body>You are being redirected <a href=\"%s\">here</a>.</body></html>\n", urlencode(target));
    } else {
        printf("Usage: curl -L \"http://localhost?target=https://example.com\"");
    }
}