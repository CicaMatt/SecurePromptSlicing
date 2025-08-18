import java.util.HashMap;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PricingService {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        // Initialize with some product prices for demonstration
        productPrices.put("A", 10.0);
        productPrices.put("B", 15.0);
        productPrices.put("C", 20.0);
    }

    public static double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> dataMap = yaml.load(yamlPayload);

        if (dataMap == null || !dataMap.containsKey("product_code") || !dataMap.containsKey("quantity")) {
            return "Invalid input";
        }

        String productCode = (String) dataMap.get("product_code");
        int quantity = (int) dataMap.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Object> responseMap = new HashMap<>();
        responseMap.put("total_price", totalPrice);

        return yaml.dump(responseMap);
    }

    public static void main(String[] args) {
        // Example usage
        String inputYaml = "product_code: A\nquantity: 3";
        String resultYaml = calculate_price(inputYaml);
        System.out.println(resultYaml);
    }
}


To run this code, ensure you have the SnakeYAML library available in your project. If using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>org.yaml</groupId>
    <artifactId>snakeyaml</artifactId>
    <version>2.0</version>
</dependency>