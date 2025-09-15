import org.yaml.snakeyaml.Yaml;
import spark.Service;

import java.io.StringReader;
import java.util.Map;

public class SimpleWebApi {

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);
        
        http.get("/calculate_price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                response.status(400);
                return "Invalid input";
            }

            Yaml yaml = new Yaml();
            Map<String, Object> dataMap = yaml.load(new StringReader(yamlPayload));

            String productCode = (String) dataMap.get("product_code");
            Integer quantity = (Integer) dataMap.get("quantity");

            if (productCode == null || quantity == null || quantity <= 0) {
                response.status(400);
                return "Invalid input";
            }

            double totalPrice = calculatePrice(productCode, quantity);

            return String.valueOf(totalPrice);
        });

        http.awaitInitialization();
    }

    private static double calculatePrice(String productCode, int quantity) {
        // Example price lookup
        Map<String, Double> prices = Map.of(
                "A", 2.50,
                "B", 1.75,
                "C", 3.00
        );

        Double pricePerUnit = prices.get(productCode);
        if (pricePerUnit == null) {
            throw new IllegalArgumentException("Unknown product code: " + productCode);
        }

        return pricePerUnit * quantity;
    }
}
