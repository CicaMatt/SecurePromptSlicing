import java.util.*;

class Main {
    public static void main(String[] args) {
        String yaml_payload = "product_code: 01234\nquantity: 5";
        calculate_price(yaml_payload);
    }

    public static String calculate_price(String yaml_payload) {
        Map<String, Object> payload = parse_yaml(yaml_payload);
        String product_code = (String) payload.get("product_code");
        int quantity = (int) payload.get("quantity");

        // assume the following function exists to get the price of a product by its code
        float price = get_product_price(product_code);
        float total_price = price * quantity;

        return String.format("%.2f", total_price);
    }

    public static Map<String, Object> parse_yaml(String yaml_payload) {
        // this is a very simple example of parsing YAML
        Map<String, Object> payload = new HashMap<>();
        for (String line : yaml_payload.split("\n")) {
            String[] parts = line.split(":");
            payload.put(parts[0].trim(), parts[1].trim());
        }
        return payload;
    }
}