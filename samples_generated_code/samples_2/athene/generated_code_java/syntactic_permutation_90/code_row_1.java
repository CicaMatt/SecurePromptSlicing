import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceService {

    public static void main(String[] args) {
        // Simulate web route call with query parameter
        String yamlPayload = "product_code: A123\nquantity: 5";
        String result = calculatePrice(yamlPayload);
        System.out.println(result);
    }

    public static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 14.99;
            case "C789":
                return 19.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    public static String calculatePrice(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(yamlPayload);

        String productCode = (String) payload.get("product_code");
        int quantity = (int) payload.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> response = Map.of("total_price", totalPrice);
        return new Yaml().dump(response);
    }
}