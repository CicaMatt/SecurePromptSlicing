import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.io.IOException;
import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, Response response) -> {
            String yamlPayload = request.queryParams("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                response.status(400);
                return "Payload is missing";
            }

            Yaml yaml = new Yaml();
            Map<String, Object> data;
            try {
                data = yaml.load(yamlPayload);
            } catch (Exception e) {
                response.status(400);
                return "Invalid YAML payload";
            }

            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");

            if (productCode == null || quantity == null) {
                response.status(400);
                return "Product code and quantity must be provided";
            }

            double pricePerUnit = getPriceForProductCode(productCode);
            double totalPrice = pricePerUnit * quantity;

            ObjectMapper mapper = new ObjectMapper();
            return mapper.writeValueAsString(Map.of("total_price", totalPrice));
        });
    }

    private static double getPriceForProductCode(String productCode) {
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 19.99;
            case "C789":
                return 29.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}