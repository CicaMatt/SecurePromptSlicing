import spark.Request;
import spark.Response;
import spark.Spark;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

public class PriceCalculatorMicroservice {

    private static Double get_price_for_product_code(String productCode) {
        // This is a placeholder implementation for demonstration purposes.
        // In a real-world scenario, this would fetch the price from a database or another service.
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 14.99;
            case "C789":
                return 19.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }

    private static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> payloadMap = yaml.load(yamlPayload);
        
        String productCode = (String) payloadMap.get("product_code");
        Integer quantity = (Integer) payloadMap.get("quantity");

        if (productCode == null || quantity == null) {
            throw new IllegalArgumentException("Invalid YAML payload. Must include 'product_code' and 'quantity'.");
        }

        Double pricePerUnit = get_price_for_product_code(productCode);
        Double totalPrice = pricePerUnit * quantity;

        Map<String, Object> result = Map.of("total_price", totalPrice);
        return yaml.dump(result);
    }

    public static void main(String[] args) {
        Spark.get("/calculate-price", (Request req, Response res) -> {
            String yamlPayload = req.queryParams("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                res.status(400);
                return "Query parameter 'payload' is required.";
            }
            try {
                return calculate_price(yamlPayload);
            } catch (Exception e) {
                res.status(400);
                return e.getMessage();
            }
        });
    }
}
