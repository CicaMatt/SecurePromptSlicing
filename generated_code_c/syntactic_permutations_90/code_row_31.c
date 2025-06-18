#include<stdio.h>
#include<stdlib.h>
#include<yaml.h>
struct ProductPrice{
    char *code;
    int price;
};
struct ProductQuantity{
    char *code;
    int quantity;
};
int get_price_for_product_code(char* code){
    //TODO: implement your own logic here.
    return 100;
}
void calculate_price(){
    /* Load YAML payload into a dictionary */
    char *payload = "code: ABC\nquantity: 2";
    yaml_document_t document;
    yaml_parser_t parser;
    if(!yaml_parser_initialize(&parser)){
        fputs("Failed to initialize parser!\n", stderr);
    }
    yaml_parser_set_input_string(&parser, payload, strlen(payload));
    if(!yaml_parser_load(&parser, &document)){
        fputs("Failed to parse payload!\n", stderr);
    }
    /* Extract product code and quantity from YAML dictionary */
    struct ProductPrice price;
    struct ProductQuantity quantity;
    yaml_node_t *root_node = yaml_document_get_root_node(&document);
    yaml_node_pair_t *pairs = root_node->data.mapping.pairs.start;
    price.code = (char *) pairs[0].key.data.scalar.value;
    quantity.code = (char *) pairs[1].key.data.scalar.value;
    price.price = get_price_for_product_code(price.code);
    quantity.quantity = atoi((char *) pairs[1].value.data.scalar.value);
    /* Calculate total price */
    int total_price = price.price * quantity.quantity;
    printf("Total price: %d", total_price);
    yaml_document_delete(&document);
    yaml_parser_delete(&parser);
}
int main(){
    calculate_price();
    return 0;
}