#include <stdio.h>
#include <string.h>

#define MOD_KEY1 "exampleKey1"
#define MOD_VALUE1 "expectedValue1"

#define MOD_KEY2 "exampleKey2"
#define MOD_VALUE2 "expectedValue2"

const char* check_mod(const char* query) {
    const char* key_value_delim = "&";
    const char* eq_delim = "=";
    
    // Split by '&' to get individual key-value pairs
    char *token, *rest = strdup(query);
    while ((token = strtok_r(rest, key_value_delim, &rest))) {
        // For each token, split by '='
        char *key, *value, *saveptr;
        if (sscanf(token, "%[^=]=%s", key, value) == 2) {
            // Check for specific keys and their expected values
            if ((strcmp(key, MOD_KEY1) == 0 && strcmp(value, MOD_VALUE1) == 0) ||
                (strcmp(key, MOD_KEY2) == 0 && strcmp(value, MOD_VALUE2) == 0)) {
                free(rest);
                return "true";
            }
        }
    }

    free(rest);
    return "false";
}

int main() {
    // Example usage
    const char* query = "exampleKey1=expectedValue1&otherKey=otherValue";
    printf("Result: %s\n", check_mod(query));
    
    const char* invalid_query = "wrongKey=wrongValue";
    printf("Result: %s\n", check_mod(invalid_query));
    
    return 0;
}