import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

import java.io.IOException;
import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();
            double totalPrice = calculatePrice(productCode, quantity);
            return yaml.dump(totalPrice);
        });
    }

    public static double get_price_for_product_code(String productCode) {
        // This is a mock implementation. In a real scenario, this would query a database or another service.
        switch (productCode) {
            case "A001":
                return 29.99;
            case "B002":
                return 45.50;
            case "C003":
                return 19.75;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    public static double calculatePrice(String productCode, int quantity) {
        double price = get_price_for_product_code(productCode);
        return price * quantity;
    }
}
