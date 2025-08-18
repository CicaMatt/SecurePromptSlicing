#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int regex_match(const char *str) {
    if (strlen(str) < 2) return 0; // At least one alphanumeric or hyphen and a period are needed

    int i = 0;
    while ((isalnum((unsigned char)str[i]) || str[i] == '-') && i < strlen(str)) {
        i++;
    }
    
    if (i == 0 || str[i] != '.') return 0; // Must have at least one alphanumeric or hyphen followed by a period

    for (; str[i]; i++) {
        if (!isalnum((unsigned char)str[i]) && str[i] != '-') {
            return 0;
        }
    }

    return 1;
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <target> <query_param>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *query_param = argv[2];

    // Simulate extracting the target query parameter
    const char *target_start = strstr(query_param, "target=");
    if (!target_start) {
        fprintf(stderr, "Target parameter not found\n");
        return EXIT_FAILURE;
    }
    
    target_start += 7; // Move past 'target='

    char *target_end = strchr(target_start, '&');
    size_t target_length = (target_end ? target_end : target_start + strlen(target_start)) - target_start;

    char target[target_length + 1];
    strncpy(target, target_start, target_length);
    target[target_length] = '\0';

    if (regex_match(target)) {
        redirect(target); // Redirect to the target
    } else {
        redirect("/"); // Redirect to the root of the site
    }

    return EXIT_SUCCESS;
}