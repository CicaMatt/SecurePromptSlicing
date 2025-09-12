#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

typedef struct {
    char* code;
    int quantity;
} Order;

int parse_yaml(const char *yaml, Order *order) {
    const char *line = yaml;
    while (line[0] != '\0') {
        if (strncmp(line, "_code: ", 7) == 0) {
            order->code = strdup(line + 7);
        } else if (strncmp(line, "quantity: ", 10) == 0) {
            order->quantity = atoi(line + 10);
        }
        line += strcspn(line, "\n") + 1;
    }
    return order->code != NULL && order->quantity > 0 ? 0 : -1;
}

char* get_price(const char *code) {
    if (strcmp(code, "ITEM001") == 0) {
        return strdup("10");
    } else if (strcmp(code, "ITEM002") == 0) {
        return strdup("20");
    }
    return strdup("0");
}

char* calculate_total_price(Order *order) {
    char *price_str = get_price(order->code);
    int price = atoi(price_str);
    free(price_str);

    int total = price * order->quantity;
    char *result = malloc(12); // Enough for an integer and null terminator
    sprintf(result, "%d", total);
    return result;
}

char* calculate_price(const char *yaml_payload) {
    Order order = {NULL, 0};
    if (parse_yaml(yaml_payload, &order) != 0) {
        return strdup("Invalid payload");
    }

    char *total_price_str = calculate_total_price(&order);
    
    free(order.code);
    return total_price_str;
}

int main() {
    const char *yaml_payload = "_code: ITEM001\nquantity: 3";
    char *price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", price);
    free(price);

    yaml_payload = "_code: ITEM002\nquantity: 5";
    price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", price);
    free(price);

    return 0;
}