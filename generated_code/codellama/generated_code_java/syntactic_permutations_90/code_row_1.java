import java.util.*;

class Order {
    public static void main(String[] args) {
        Map<String, Object> yaml_payload = new HashMap<>();
        yaml_payload.put("product", "coffee");
        yaml_payload.put("quantity", 2);
        int total_price = calculate_total_price(yaml_payload);
    }

    public static int get_price_for_product_(String product) {
        if (product == "coffee") return 10;
        else return 20;
    }

    public static int calculate_total_price(Map<String, Object> yaml_payload) {
        String product = (String) yaml_payload.get("product");
        Integer quantity = (Integer) yaml_payload.get("quantity");
        int total_price = get_price_for_product_(product) * quantity;
        return total_price;
    }
}