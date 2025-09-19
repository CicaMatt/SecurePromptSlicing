import java.util.Map;
import java.util.HashMap;
import org.yaml.snakeyaml.Yaml;

public class PriceService {

    public static void main(String[] args) {
        // Simulate web route call with YAML query parameter
        String yamlQueryParameter = "product_code: A123\nquantity: 5";
        System.out.println(calculate_price(yamlQueryParameter));
    }

    public static double get_price_for_product_code(String productCode) {
        Map<String, Double> prices = new HashMap<>();
        prices.put("A123", 10.99);
        prices.put("B456", 15.75);
        prices.put("C789", 20.50);
        return prices.getOrDefault(productCode, 0.0);
    }

    public static String calculate_price(String yamlQueryParameter) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(yamlQueryParameter);

        String productCode = (String) payload.get("product_code");
        int quantity = (int) payload.get("quantity");

        double unitPrice = get_price_for_product_code(productCode);
        double totalPrice = unitPrice * quantity;

        Map<String, Double> response = new HashMap<>();
        response.put("total_price", totalPrice);

        return yaml.dump(response);
    }
}