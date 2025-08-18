#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair* items;
    size_t count;
} KeyValuePairs;

KeyValuePairs parse_yaml(const char* yaml) {
    KeyValuePairs pairs = {NULL, 0};
    const char* line = yaml;
    
    while (*line != '\0') {
        if (strchr(line, ':')) {
            char key[MAX_LINE_LENGTH] = {0};
            char value[MAX_LINE_LENGTH] = {0};
            
            char* colon_pos = strchr(line, ':');
            strncpy(key, line, colon_pos - line);
            key[colon_pos - line] = '\0';
            
            char* start_value_pos = strchr(colon_pos + 1, ' ');
            if (start_value_pos) {
                strcpy(value, start_value_pos + 1);
            } else {
                strcpy(value, colon_pos + 2); // Skip ": "
            }
            
            pairs.count++;
            pairs.items = realloc(pairs.items, pairs.count * sizeof(KeyValuePair));
            pairs.items[pairs.count - 1].key = strdup(key);
            pairs.items[pairs.count - 1].value = strdup(value);
        }

        line = strchr(line, '\n');
        if (line) {
            line++;
        }
    }
    
    return pairs;
}

char* calculate_price(const char* yaml_payload) {
    KeyValuePairs pairs = parse_yaml(yaml_payload);

    const char* product_code = NULL;
    int quantity = 0;

    for (size_t i = 0; i < pairs.count; ++i) {
        if (strcmp(pairs.items[i].key, "product_code") == 0) {
            product_code = pairs.items[i].value;
        } else if (strcmp(pairs.items[i].key, "quantity") == 0) {
            quantity = atoi(pairs.items[i].value);
        }
    }

    int price_per_unit = 10; // Assume a fixed price per unit for simplicity

    char* result = malloc(MAX_LINE_LENGTH * sizeof(char));
    if (product_code && quantity > 0) {
        sprintf(result, "Total Price: %d", price_per_unit * quantity);
    } else {
        strcpy(result, "Invalid input");
    }

    for (size_t i = 0; i < pairs.count; ++i) {
        free(pairs.items[i].key);
        free(pairs.items[i].value);
    }
    free(pairs.items);

    return result;
}

int main() {
    const char* yaml_payload = "product_code: ABC123\nquantity: 5";
    char* price_result = calculate_price(yaml_payload);
    printf("%s\n", price_result);
    free(price_result);
    return 0;
}