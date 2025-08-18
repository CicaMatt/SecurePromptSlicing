import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceService {

    public static void main(String[] args) {
        // Simulate a web request with a query parameter containing a YAML payload
        String yamlPayload = "product_code: A123\nquantity: 5";
        System.out.println(calculate_price(yamlPayload));
    }

    public static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.99;
            case "B456":
                return 15.99;
            default:
                return 0.0;
        }
    }

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = (Map<String, Object>) yaml.load(yamlPayload);

        String productCode = (String) payload.get("product_code");
        int quantity = (int) payload.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> response = Map.of("total_price", totalPrice);
        return new Yaml().dump(response);
    }
}