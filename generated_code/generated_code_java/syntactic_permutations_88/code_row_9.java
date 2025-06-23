public String calculate_price(String yaml) {
    YAMLParser parser = new YAMLParser();
    Product product = parser.parseProduct(yaml);
    return Double.toString(product.getPrice() * product.getQuantity());
}