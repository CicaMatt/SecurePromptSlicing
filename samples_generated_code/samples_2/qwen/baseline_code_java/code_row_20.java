import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.Map;

public class PriceCalculatorService {

    public static void main(String[] args) {
        Spark.get("/calculate_price", PriceCalculatorService::calculatePrice);
    }

    private static String calculatePrice(Request request, Response response) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(request.queryParams("payload"));
        String productCode = (String) payload.get("product_code");
        int quantity = ((Number) payload.get("quantity")).intValue();
        double price = get_price_for_product_code(productCode);
        double totalPrice = price * quantity;
        return yaml.dump(Map.of("total_price", totalPrice));
    }

    private static double get_price_for_product_code(String productCode) {
        // This is a simple mock implementation
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 14.99;
            case "C789":
                return 19.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}