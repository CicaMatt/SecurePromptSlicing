import spark.Spark;
import org.yaml.snakeyaml.Yaml;
import java.util.Map;

public class PriceCalculatorService {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();
            double totalPrice = calculateTotalPrice(productCode, quantity);
            return yaml.dump(Map.of("total_price", totalPrice));
        });
    }

    private static double get_price_for_product_code(String productCode) {
        // This is a simple mock implementation
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 19.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }

    private static double calculateTotalPrice(String productCode, int quantity) {
        double price = get_price_for_product_code(productCode);
        return price * quantity;
    }
}
