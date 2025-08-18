import java.util.Map;
import java.util.HashMap;
import org.yaml.snakeyaml.Yaml;

public class PricingService {

    public static double get_price_for_product_code(String productCode) {
        Map<String, Double> prices = new HashMap<>();
        prices.put("A123", 10.5);
        prices.put("B456", 20.9);
        prices.put("C789", 5.25);
        return prices.getOrDefault(productCode, 0.0);
    }

    public static double calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = (Map<String, Object>) yaml.load(yamlPayload);

        String productCode = (String) payload.get("product_code");
        int quantity = (int) payload.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        return pricePerUnit * quantity;
    }

    public static void main(String[] args) {
        String yamlPayload = "product_code: A123\nquantity: 5";
        double totalPrice = calculate_price(yamlPayload);
        System.out.println("Total Price: " + totalPrice);
    }
}