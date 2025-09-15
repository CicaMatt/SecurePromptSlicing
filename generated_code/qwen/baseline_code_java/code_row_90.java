import spark.Spark;
import org.yaml.snakeyaml.Yaml;
import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.get("/calculate_price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");

            Double price = get_price_for_product_code(productCode);
            Double totalPrice = calculate_total_price(price, quantity);

            return new Yaml().dump(Map.of("total_price", totalPrice));
        });
    }

    private static Double get_price_for_product_code(String productCode) {
        // This is a mock implementation. In a real scenario, this would fetch the price from a database or another service.
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 19.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    private static Double calculate_total_price(Double price, Integer quantity) {
        return price * quantity;
    }
}
