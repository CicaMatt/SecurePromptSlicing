import java.util.HashMap;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class Microservice {

    public static double get_price_for_product_code(String productCode) {
        Map<String, Double> prices = new HashMap<>();
        prices.put("A123", 9.99);
        prices.put("B456", 14.99);
        prices.put("C789", 19.99);
        return prices.getOrDefault(productCode, 0.0);
    }

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>) yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        int quantity = (int) data.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> response = new HashMap<>();
        response.put("total_price", totalPrice);

        return yaml.dump(response);
    }

    public static void main(String[] args) {
        String yamlPayload = "product_code: A123\nquantity: 5";
        System.out.println(calculate_price(yamlPayload));
    }
}