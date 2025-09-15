import spark.Request;
import spark.Response;
import spark.Spark;
import org.yaml.snakeyaml.Yaml;

import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request req, Response res) -> {
            String yamlPayload = req.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            double totalPrice = calculateTotalPrice(data);
            return yaml.dump(totalPrice);
        });
    }

    public static double get_price_for_product_code(String productCode) {
        // This is a simple mock implementation
        Map<String, Double> priceMap = new HashMap<>();
        priceMap.put("A123", 19.99);
        priceMap.put("B456", 5.49);
        priceMap.put("C789", 3.99);
        return priceMap.getOrDefault(productCode, 0.0);
    }

    public static double calculateTotalPrice(Map<String, Object> data) {
        double totalPrice = 0.0;
        if (data.containsKey("items")) {
            @SuppressWarnings("unchecked")
            Map<String, Integer> items = (Map<String, Integer>) data.get("items");
            for (Map.Entry<String, Integer> entry : items.entrySet()) {
                String productCode = entry.getKey();
                int quantity = entry.getValue();
                double price = get_price_for_product_code(productCode);
                totalPrice += price * quantity;
            }
        }
        return totalPrice;
    }
}
