#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LEN 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }

    char url[MAX_URL_LEN];
    strncpy(url, argv[1], sizeof(url));
    url[sizeof(url) - 1] = '\0';

    // Extract the query part from the URL
    char *query_start = strchr(url, '?');
    if (!query_start) {
        printf("http://root-of-the-site/\n");
        return 0;
    }

    char *target_query_param = strstr(query_start, "target=");
    if (!target_query_param || target_query_param == query_start) {
        printf("http://root-of-the-site/\n");
        return 0;
    }

    // Move past the 'target=' part
    target_query_param += strlen("target=");

    // Find the end of the value (either a '&' or the end of the string)
    char *value_end = strchr(target_query_param, '&');
    if (!value_end) {
        value_end = target_query_param + strlen(target_query_param);
    }

    int target_value_length = value_end - target_query_param;
    char target_value[target_value_length + 1];
    strncpy(target_value, target_query_param, target_value_length);
    target_value[target_value_length] = '\0';

    // Check if the target matches the regular expression
    for (int i = 0; target_value[i]; ++i) {
        if (!((target_value[i] >= 'a' && target_value[i] <= 'z') ||
              (target_value[i] >= 'A' && target_value[i] <= 'Z') ||
              (target_value[i] >= '0' && target_value[i] <= '9') ||
              target_value[i] == '-')) {
            if (!(i == 0 && target_value[i] == '.')) {
                printf("http://root-of-the-site/\n");
                return 0;
            }
        } else if (target_value[i] == '.') {
            // Check if the dot is at the correct position
            int valid = 1;
            for (int j = i + 1; target_value[j]; ++j) {
                if (!((target_value[j] >= 'a' && target_value[j] <= 'z') ||
                      (target_value[j] >= 'A' && target_value[j] <= 'Z') ||
                      (target_value[j] >= '0' && target_value[j] <= '9'))) {
                    valid = 0;
                    break;
                }
            }
            if (!valid) {
                printf("http://root-of-the-site/\n");
                return 0;
            }

            // If dot is at the end, redirect to root
            if (target_value[i + 1] == '\0') {
                printf("http://root-of-the-site/\n");
                return 0;
            }
        }
    }

    printf("http://%s\n", target_value);
    return 0;
}