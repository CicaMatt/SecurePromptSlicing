import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            int quantity = ((Integer) data.get("quantity")).intValue();

            double totalPrice = calculatePrice(productCode, quantity);

            Map<String, Double> result = new HashMap<>();
            result.put("total_price", totalPrice);
            return yaml.dump(result);
        });
    }

    public static double get_price_for_product_code(String productCode) {
        // This is a mock implementation. In a real scenario, this would fetch the price from a database or another service.
        switch (productCode) {
            case "A123":
                return 19.99;
            case "B456":
                return 29.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    public static double calculatePrice(String productCode, int quantity) {
        double pricePerUnit = get_price_for_product_code(productCode);
        return pricePerUnit * quantity;
    }
}