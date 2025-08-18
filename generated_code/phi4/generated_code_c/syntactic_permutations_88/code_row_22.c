#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

struct PriceData {
    char _code[50];
    int quantity;
};

int parse_yaml_payload(const char *payload, struct PriceData *data) {
    const char *_key_start = "_code: ";
    const char *quantity_start = "quantity: ";

    char *_code_position = strstr(payload, _key_start);
    if (_code_position == NULL) return 0;

    _code_position += strlen(_key_start);
    char *end_of_code = strchr(_code_position, '\n');
    strncpy(data->_code, _code_position, end_of_code - _code_position);
    data->_code[end_of_code - _code_position] = '\0';

    char *quantity_position = strstr(payload, quantity_start);
    if (quantity_position == NULL) return 0;

    quantity_position += strlen(quantity_start);
    data->quantity = atoi(quantity_position);

    return 1;
}

int calculate_price(const struct PriceData *data, int price_per_item, char *result, size_t result_size) {
    int total_price = data->quantity * price_per_item;
    snprintf(result, result_size, "%d", total_price);
    return 0;
}

char* simulate_query_param(const char *payload) {
    static char query_buffer[MAX_PAYLOAD_SIZE];
    snprintf(query_buffer, MAX_PAYLOAD_SIZE, "payload=%s", payload);
    return query_buffer;
}

int main() {
    const char *yaml_payload = "_code: ITEM123\nquantity: 4";
    struct PriceData data;

    if (!parse_yaml_payload(yaml_payload, &data)) {
        printf("Error parsing YAML payload\n");
        return 1;
    }

    int price_per_item = 10; // Assume a fixed price per item for this example
    char total_price_string[20];

    calculate_price(&data, price_per_item, total_price_string, sizeof(total_price_string));

    printf("Total Price: %s\n", total_price_string);

    return 0;
}