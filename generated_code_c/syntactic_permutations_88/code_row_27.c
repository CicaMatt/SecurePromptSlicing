int calculate_price(const char* yaml) {
    // parse YAML payload
    int product_code = 0;
    int quantity = 0;
    sscanf(yaml, "product_code: %d\nquantity: %d", &product_code, &quantity);
    
    // lookup price of the product
    int price = get_price_from_db(product_code);
    
    // calculate total price by multiplying quantity and price
    return price * quantity;
}