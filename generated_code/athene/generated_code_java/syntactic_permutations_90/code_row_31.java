import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculatorService {

    public static void main(String[] args) {
        // Simulate web route call with YAML query parameter
        String yamlQuery = "product_code: 12345\nquantity: 10";
        System.out.println(calculatePrice(yamlQuery));
    }

    private static double get_price_for_product_code(int productCode) {
        // Mocked price retrieval based on product code
        return switch (productCode) {
            case 12345 -> 9.99;
            case 67890 -> 14.99;
            default -> 0.0;
        };
    }

    public static String calculatePrice(String yamlQuery) {
        Yaml yaml = new Yaml();
        Map<String, Object> queryMap = yaml.load(yamlQuery);

        int productCode = (int) queryMap.get("product_code");
        int quantity = (int) queryMap.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> response = Map.of("total_price", totalPrice);
        return new Yaml().dump(response);
    }
}