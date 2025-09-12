import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Route;

import java.util.Map;

public class PriceCalculatorService {

    public static void main(String[] args) {
        spark.Spark.get("/calculate_price", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String yamlPayload = request.queryParams("payload");
                Yaml yaml = new Yaml();
                Map<String, Object> payload = (Map<String, Object>) yaml.load(yamlPayload);
                String productCode = (String) payload.get("product_code");
                Integer quantity = (Integer) payload.get("quantity");
                double totalPrice = calculatePrice(productCode, quantity);
                response.type("application/x-yaml");
                return "total_price: " + totalPrice;
            }
        });
    }

    private static double calculatePrice(String productCode, int quantity) {
        double pricePerUnit = get_price_for_product_code(productCode);
        return pricePerUnit * quantity;
    }

    private static double get_price_for_product_code(String productCode) {
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