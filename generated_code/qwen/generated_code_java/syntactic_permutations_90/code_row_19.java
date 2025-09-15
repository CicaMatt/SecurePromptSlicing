import spark.Request;
import spark.Spark;
import org.yaml.snakeyaml.Yaml;

import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);

            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();

            double price = get_price_for_product_code(productCode);
            double totalPrice = calculate_price(price, quantity);

            Map<String, Double> result = new HashMap<>();
            result.put("total_price", totalPrice);
            return yaml.dump(result);
        });
    }

    private static double get_price_for_product_code(String productCode) {
        // This is a simple mock implementation.
        // In a real application, this would query a database or another service.
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 19.99;
            case "C789":
                return 29.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }

    private static double calculate_price(double price, int quantity) {
        return price * quantity;
    }
}
