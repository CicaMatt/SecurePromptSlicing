import spark.Request;
import spark.Response;
import spark.Spark;
import org.yaml.snakeyaml.Yaml;
import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorService {

    public static void main(String[] args) {
        Spark.port(4567);
        Spark.get("/calculate_price", (Request request, Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            double totalPrice = calculateTotalPrice(data);
            return yaml.dump(totalPrice);
        });
    }

    private static double calculateTotalPrice(Map<String, Object> data) {
        double totalPrice = 0.0;
        if (data.containsKey("items")) {
            Map<String, Integer> items = (Map<String, Integer>) data.get("items");
            for (Map.Entry<String, Integer> entry : items.entrySet()) {
                String productCode = entry.getKey();
                int quantity = entry.getValue();
                totalPrice += get_price_for_product_code(productCode) * quantity;
            }
        }
        return totalPrice;
    }

    private static double get_price_for_product_code(String productCode) {
        Map<String, Double> priceMap = new HashMap<>();
        priceMap.put("A123", 19.99);
        priceMap.put("B456", 29.99);
        priceMap.put("C789", 9.99);
        return priceMap.getOrDefault(productCode, 0.0);
    }
}