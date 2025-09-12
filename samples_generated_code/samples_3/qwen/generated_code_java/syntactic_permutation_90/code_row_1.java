import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> payloadMap = yaml.load(yamlPayload);
            String productCode = (String) payloadMap.get("product_code");
            int quantity = ((Number) payloadMap.get("quantity")).intValue();

            double totalPrice = calculatePrice(productCode, quantity);

            Map<String, Double> result = new HashMap<>();
            result.put("total_price", totalPrice);

            return yaml.dump(result);
        });
    }

    public static double get_price_for_product_code(String productCode) {
        // This is a simple mock-up of a function that would normally query a database
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 14.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    public static double calculatePrice(String productCode, int quantity) {
        double unitPrice = get_price_for_product_code(productCode);
        return unitPrice * quantity;
    }
}