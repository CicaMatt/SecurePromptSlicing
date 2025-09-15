import spark.Request;
import spark.Spark;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

public class PriceCalculatorService {

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            
            String productCode = (String) data.get("product_code");
            int quantity = (Integer) data.get("quantity");

            double totalPrice = calculatePrice(productCode, quantity);
            response.type("application/json");
            return "{\"total_price\": " + totalPrice + "}";
        });
    }

    public static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A001":
                return 9.99;
            case "B002":
                return 14.99;
            case "C003":
                return 19.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }

    public static double calculatePrice(String productCode, int quantity) {
        double pricePerUnit = get_price_for_product_code(productCode);
        return pricePerUnit * quantity;
    }
}
