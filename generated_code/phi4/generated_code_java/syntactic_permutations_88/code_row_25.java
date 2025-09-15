import org.yaml.snakeyaml.Yaml;
import spark.Spark;

import java.io.IOException;
import java.util.Map;

public class SimpleWebAPI {

    private static final Map<String, Double> productPrices = Map.of(
            "A1", 10.0,
            "B2", 20.0,
            "C3", 30.0
    );

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.post("/calculate_price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                response.status(400);
                return "Invalid payload";
            }

            try {
                Yaml yaml = new Yaml();
                Map<String, Object> data = yaml.load(yamlPayload);

                String productCode = (String) data.get("product_code");
                Integer quantity = (Integer) data.get("quantity");

                if (productCode == null || quantity == null || !productPrices.containsKey(productCode)) {
                    response.status(400);
                    return "Invalid product code or quantity";
                }

                double price = productPrices.get(productCode);
                double totalPrice = price * quantity;

                return String.format("Total Price: %.2f", totalPrice);

            } catch (Exception e) {
                response.status(500);
                return "Error processing request";
            }
        });

        Spark.awaitInitialization();
    }
}
