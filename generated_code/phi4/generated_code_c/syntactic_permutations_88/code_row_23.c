#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    double price;
} Product;

Product products[] = {
    {"A", 10.0},
    {"B", 20.0},
    {"C", 30.0}
};

const int product_count = sizeof(products) / sizeof(Product);

double get_product_price(const char* product_code) {
    for (int i = 0; i < product_count; ++i) {
        if (strcmp(products[i].product_code, product_code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Product not found
}

void calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    
    FILE *file = fmemopen((void*)yaml_payload, strlen(yaml_payload), "r");
    if (!file) {
        fprintf(stderr, "Failed to open YAML payload\n");
        return;
    }

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser\n");
        fclose(file);
        return;
    }
    
    yaml_parser_set_input_file(&parser, file);

    const char *product_code = NULL;
    int quantity = 0;

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            break;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (!product_code) {
                    product_code = strdup((char*)event.data.scalar.value);
                } else if (quantity == 0) {
                    quantity = atoi((char*)event.data.scalar.value);
                }
                break;

            case YAML_STREAM_END_EVENT:
                goto end;
        }

        yaml_event_delete(&event);
    }

end:
    yaml_event_delete(&event);
    yaml_parser_delete(&parser);
    fclose(file);

    if (product_code && quantity > 0) {
        double price = get_product_price(product_code);
        if (price != -1.0) {
            double total_price = price * quantity;
            printf("Total Price: %.2f\n", total_price);
        } else {
            fprintf(stderr, "Product not found\n");
        }
    } else {
        fprintf(stderr, "Invalid YAML payload\n");
    }

    free((void*)product_code);
}

int main() {
    const char* yaml_payload = 
        "---\n"
        "product_code: A\n"
        "quantity: 3\n";

    calculate_price(yaml_payload);

    return 0;
}