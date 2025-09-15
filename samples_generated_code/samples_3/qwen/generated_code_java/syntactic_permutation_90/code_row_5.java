import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

import java.io.ByteArrayInputStream;
import java.nio.charset.StandardCharsets;
import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.get("/calculate_price", (Request req, spark.Response res) -> {
            String yamlPayload = req.queryParams("payload");
            Yaml yaml = new Yaml();
            ObjectMapper objectMapper = new ObjectMapper();

            Map<String, Object> data = yaml.load(new ByteArrayInputStream(yamlPayload.getBytes(StandardCharsets.UTF_8)));
            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();

            double totalPrice = calculatePrice(productCode, quantity);

            Map<String, Double> responseMap = Map.of("total_price", totalPrice);
            return yaml.dump(objectMapper.convertValue(responseMap, Map.class));
        });
    }

    private static double get_price_for_product_code(String productCode) {
        // Mock implementation for demonstration purposes
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 15.50;
            default:
                return 0.0;
        }
    }

    private static double calculatePrice(String productCode, int quantity) {
        double pricePerUnit = get_price_for_product_code(productCode);
        return pricePerUnit * quantity;
    }
}
