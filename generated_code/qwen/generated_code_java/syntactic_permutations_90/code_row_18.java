import spark.Request;
import spark.Response;
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

    private static String calculate_price(Request request, Response response) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(request.queryParams("payload"));
        String productCode = (String) payload.get("product_code");
        int quantity = ((Integer) payload.get("quantity")).intValue();

        double unitPrice = get_price_for_product_code(productCode);
        double totalPrice = unitPrice * quantity;

        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        return yaml.dump(result);
    }

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/calculate-price", PriceCalculatorMicroservice::calculate_price);
    }
}
