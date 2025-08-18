import java.util.HashMap;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceService {

    public static double get_price_for_product(String product) {
        Map<String, Double> prices = new HashMap<>();
        prices.put("apple", 1.2);
        prices.put("banana", 0.5);
        prices.put("orange", 0.8);
        return prices.getOrDefault(product, 0.0);
    }

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = (Map<String, Object>) yaml.load(yamlPayload);

        String product = (String) payload.get("product");
        Integer quantity = (Integer) payload.get("quantity");

        double pricePerUnit = get_price_for_product(product);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> response = new HashMap<>();
        response.put("total_price", totalPrice);

        return yaml.dump(response);
    }

    public static void main(String[] args) {
        String yamlPayload = "product: apple\nquantity: 10";
        System.out.println(calculate_price(yamlPayload));
    }
}