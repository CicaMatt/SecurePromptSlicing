import org.yaml.snakeyaml.Yaml;
import spark.Spark;

import java.io.InputStream;
import java.util.Map;

public class PriceCalculatorApi {

    public static void main(String[] args) {
        Spark.port(8080);
        
        Spark.get("/calculate_price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                response.status(400);
                return "Invalid payload";
            }

            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            
            if (data == null || !data.containsKey("product_code") || !data.containsKey("quantity")) {
                response.status(400);
                return "Missing product_code or quantity in payload";
            }

            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");

            if (quantity == null || quantity < 0) {
                response.status(400);
                return "Invalid quantity value";
            }

            double pricePerUnit = getPriceForProduct(productCode);

            if (pricePerUnit == -1.0) {
                response.status(404);
                return "Product not found";
            }

            double totalPrice = pricePerUnit * quantity;
            
            return String.valueOf(totalPrice);
        });
    }

    private static double getPriceForProduct(String productCode) {
        // This is a simple hardcoded lookup for demonstration purposes
        switch (productCode.toLowerCase()) {
            case "apple":
                return 0.5;
            case "banana":
                return 0.3;
            case "orange":
                return 0.4;
            default:
                return -1.0; // Product not found
        }
    }
}
