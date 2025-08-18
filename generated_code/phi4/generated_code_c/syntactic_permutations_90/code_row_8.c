#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

void free_dict(KeyValuePair **dict, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        free(dict[i]->key);
        free(dict[i]->value);
        free(dict[i]);
    }
    free(dict);
}

KeyValuePair* load_yaml_to_dict(const char *yaml_str, size_t *len) {
    KeyValuePair **dict = NULL;
    char *copy = strdup(yaml_str);
    char *line = strtok(copy, "\n");
    *len = 0;

    while (line != NULL) {
        if (strchr(line, ':') != NULL) {
            (*len)++;
            dict = realloc(dict, sizeof(KeyValuePair*) * (*len));
            KeyValuePair *pair = malloc(sizeof(KeyValuePair));
            pair->key = strndup(line, strchr(line, ':') - line);
            pair->value = strdup(strchr(line, ':') + 1);
            if (pair->value[0] == ' ') {
                memmove(pair->value, pair->value + 1, strlen(pair->value));
            }
            dict[*len - 1] = pair;
        }
        line = strtok(NULL, "\n");
    }

    free(copy);
    return *dict ? dict : NULL;
}

double get_price_for_product_code(const char *yaml_query) {
    size_t len = 0;
    KeyValuePair *dict = load_yaml_to_dict(yaml_query, &len);

    if (dict == NULL || len < 2) {
        fprintf(stderr, "Invalid YAML payload\n");
        exit(EXIT_FAILURE);
    }

    const char *product_code = NULL;
    double price_per_item = 0.0;
    int quantity = 0;

    for (size_t i = 0; i < len; ++i) {
        if (strcmp(dict[i]->key, "product_code") == 0) {
            product_code = dict[i]->value;
        } else if (strcmp(dict[i]->key, "price_per_item") == 0) {
            price_per_item = atof(dict[i]->value);
        } else if (strcmp(dict[i]->key, "quantity") == 0) {
            quantity = atoi(dict[i]->value);
        }
    }

    free_dict(&dict, len);

    if (!product_code || price_per_item <= 0 || quantity < 1) {
        fprintf(stderr, "Missing or invalid parameters\n");
        exit(EXIT_FAILURE);
    }

    return price_per_item * quantity;
}

void generate_yaml_response(double total_price) {
    printf("---\n");
    printf("total_price: %f\n", total_price);
}

int main() {
    const char *yaml_payload = 
        "product_code: ABC123\n"
        "price_per_item: 10.0\n"
        "quantity: 3\n";

    double total_price = get_price_for_product_code(yaml_payload);
    generate_yaml_response(total_price);

    return 0;
}