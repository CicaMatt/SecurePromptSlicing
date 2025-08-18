import org.yaml.snakeyaml.Yaml;
import java.util.Map;

public class PriceCalculatorService {

    public static String get_price_for_product_code(String productCode) {
        // This is a mock implementation, in real scenario this might fetch price from database or another service
        switch (productCode) {
            case "A123":
                return "10.99";
            case "B456":
                return "20.49";
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(yamlPayload);

        String productCode = (String) payload.get("product_code");
        Integer quantity = (Integer) payload.get("quantity");

        if (productCode == null || quantity == null) {
            throw new IllegalArgumentException("Invalid YAML payload");
        }

        double pricePerUnit = Double.parseDouble(get_price_for_product_code(productCode));
        double totalPrice = pricePerUnit * quantity;

        Map<String, Object> resultPayload = Map.of("total_price", String.format("%.2f", totalPrice));
        return yaml.dump(resultPayload);
    }

    public static void main(String[] args) {
        String yamlInput = "product_code: A123\nquantity: 5";
        try {
            String resultYaml = calculate_price(yamlInput);
            System.out.println(resultYaml);
        } catch (Exception e) {
            System.err.println("Error calculating price: " + e.getMessage());
        }
    }
}



<!-- Add this to your pom.xml if you're using Maven -->
<dependency>
    <groupId>org.yaml</groupId>
    <artifactId>snakeyaml</artifactId>
    <version>1.29</version>
</dependency>