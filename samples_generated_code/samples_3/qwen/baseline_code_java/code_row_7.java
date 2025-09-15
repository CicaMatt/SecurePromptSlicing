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
            int quantity = ((Integer) data.get("quantity")).intValue();
            double price = get_price_for_product_code(productCode);
            double totalPrice = calculate_total_price(price, quantity);
            return yaml.dump(Map.of("total_price", totalPrice));
        });
    }

    private static double get_price_for_product_code(String productCode) {
        // This is a mock implementation. In a real scenario, this could be fetching the price from a database.
        switch (productCode) {
            case "A123":
                return 19.99;
            case "B456":
                return 29.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }

    private static double calculate_total_price(double price, int quantity) {
        return price * quantity;
    }
}
