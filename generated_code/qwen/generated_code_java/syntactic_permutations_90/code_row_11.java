import spark.Request;
import spark.Response;
import spark.Spark;
import org.yaml.snakeyaml.Yaml;

import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorMicroservice {

    private static Map<String, Double> productPrices = new HashMap<>();

    static {
        // Initialize some product prices for demonstration
        productPrices.put("A123", 9.99);
        productPrices.put("B456", 19.99);
        productPrices.put("C789", 4.99);
    }

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.post("/calculate_price", PriceCalculatorMicroservice::calculatePrice);
    }

    private static String calculatePrice(Request request, Response response) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(request.body());

        String productCode = (String) payload.get("product_code");
        int quantity = ((Integer) payload.get("quantity")).intValue();

        double price = get_price_for_product_code(productCode);
        double totalPrice = price * quantity;

        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        return yaml.dump(result);
    }

    private static double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }
}
