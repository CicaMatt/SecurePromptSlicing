import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

import java.io.StringReader;
import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorApi {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A123", 19.99);
        productPrices.put("B456", 29.99);
        productPrices.put("C789", 39.99);
    }

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request req, spark.Response res) -> {
            String yamlPayload = req.queryParams("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                return "Invalid request: payload is required";
            }
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(new StringReader(yamlPayload));
            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");

            if (productCode == null || quantity == null) {
                return "Invalid request: product_code and quantity are required";
            }

            Double price = productPrices.get(productCode);
            if (price == null) {
                return "Product not found";
            }

            double totalPrice = price * quantity;
            return String.format("Total Price: %.2f", totalPrice);
        });
    }
}
