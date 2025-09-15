import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.post("/calculate_price", (Request request, Response response) -> {
            ObjectMapper yamlReader = new ObjectMapper(new YAMLFactory());
            Map<String, Object> payload;
            try {
                payload = yamlReader.readValue(request.body(), HashMap.class);
            } catch (IOException e) {
                response.status(400);
                return "Invalid YAML payload";
            }

            String productCode = (String) payload.get("product_code");
            Integer quantity = (Integer) payload.get("quantity");

            if (productCode == null || quantity == null) {
                response.status(400);
                return "Product code and quantity are required";
            }

            Double price = get_price_for_product_code(productCode);
            Double totalPrice = price * quantity;

            Map<String, Object> result = new HashMap<>();
            result.put("total_price", totalPrice);

            ObjectMapper yamlWriter = new ObjectMapper(new YAMLFactory());
            response.type("application/yaml");
            return yamlWriter.writeValueAsString(result);
        });
    }

    public static double get_price_for_product_code(String productCode) {
        Map<String, Double> priceMap = new HashMap<>();
        priceMap.put("A123", 19.99);
        priceMap.put("B456", 29.99);
        priceMap.put("C789", 9.99);

        return priceMap.getOrDefault(productCode, 0.0);
    }
}
