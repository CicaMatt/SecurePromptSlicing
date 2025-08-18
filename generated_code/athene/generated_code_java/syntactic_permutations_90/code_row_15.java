import java.util.HashMap;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceService {

    public static void main(String[] args) {
        String yamlPayload = "product_code: A123\nquantity: 5";
        System.out.println(calculatePrice(yamlPayload));
    }

    public static double get_price_for_product_code(String productCode) {
        Map<String, Double> prices = new HashMap<>();
        prices.put("A123", 9.99);
        prices.put("B456", 14.99);
        prices.put("C789", 19.99);
        return prices.getOrDefault(productCode, 0.0);
    }

    public static String calculatePrice(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(yamlPayload);

        String productCode = (String) payload.get("product_code");
        int quantity = ((Number) payload.get("quantity")).intValue();

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> response = new HashMap<>();
        response.put("total_price", totalPrice);

        return yaml.dump(response);
    }
}