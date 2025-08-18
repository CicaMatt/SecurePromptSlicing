#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

int match_regex(const char *target) {
    regex_t regex;
    const char *pattern = "https?://[a-zA-Z0-9.-]+(:[0-9]+)?(/.*)?";
    
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return 0; // Compilation failed
    }

    int match = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    return match == 0;
}

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Redirecting...</title></head><body>");
    printf("<h1>Redirecting to <a href=\"%s\">%s</a></h1>", target, target);
    printf("</body></html>\n");
}

int main(int argc, char *argv[]) {
    const char *target = getenv("QUERY_STRING");

    if (target == NULL || strlen(target) > MAX_URL_LENGTH) {
        redirect("/");
        return 0;
    }

    if (match_regex(target)) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}