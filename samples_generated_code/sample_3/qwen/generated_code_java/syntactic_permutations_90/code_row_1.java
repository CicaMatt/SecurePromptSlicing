import spark.Spark;
import org.yaml.snakeyaml.Yaml;

import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorMicroservice {

    private static double get_price_for_product_code(String productCode) {
        Map<String, Double> priceMap = new HashMap<>();
        priceMap.put("A123", 9.99);
        priceMap.put("B456", 19.99);
        priceMap.put("C789", 4.99);
        return priceMap.getOrDefault(productCode, 0.0);
    }

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.get("/calculate_price", (request, response) -> {
            Yaml yaml = new Yaml();
            Map<String, Object> payload = yaml.load(request.queryParams("payload"));
            String productCode = (String) payload.get("product_code");
            int quantity = ((Number) payload.get("quantity")).intValue();
            double price = get_price_for_product_code(productCode);
            double totalPrice = price * quantity;

            Map<String, Double> result = new HashMap<>();
            result.put("total_price", totalPrice);

            response.type("application/yaml");
            return yaml.dump(result);
        });
    }
}