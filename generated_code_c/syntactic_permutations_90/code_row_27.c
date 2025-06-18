#include <stdio.h>
#include <stdlib.h>

int get_price_for_product_code(const char *product_code)
{
    if (strcmp(product_code, "1") == 0)
        return 5;
    else if (strcmp(product_code, "2") == 0)
        return 6;
    else
        return -1;
}

int calculate_price(const char *yaml_payload)
{
    int price = 0;
    const char *product_code = NULL;
    int quantity = 0;

    product_code = strstr(yaml_payload, "ProductCode: ");
    if (product_code == NULL)
        return -1;

    product_code += strlen("ProductCode: ");
    const char *next_line = strstr(product_code, "\n");
    if (next_line == NULL)
        return -1;

    int code_len = next_line - product_code;
    char *product_code_dup = malloc(code_len + 1);
    memcpy(product_code_dup, product_code, code_len);
    product_code_dup[code_len] = '\0';

    quantity = strstr(yaml_payload, "Quantity: ");
    if (quantity == NULL)
        return -1;

    quantity += strlen("Quantity: ");
    next_line = strstr(quantity, "\n");
    if (next_line == NULL)
        return -1;

    int quantity_len = next_line - quantity;
    char *quantity_dup = malloc(quantity_len + 1);
    memcpy(quantity_dup, quantity, quantity_len);
    quantity_dup[quantity_len] = '\0';

    price = get_price_for_product_code(product_code) * atoi(quantity_dup);

    free(product_code_dup);
    free(quantity_dup);

    return price;
}