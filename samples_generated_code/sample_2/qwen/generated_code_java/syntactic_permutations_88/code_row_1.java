import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorApi {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();

            // Mocked price retrieval based on product code
            Map<String, Double> productPrices = new HashMap<>();
            productPrices.put("A123", 19.99);
            productPrices.put("B456", 29.99);

            double price = productPrices.getOrDefault(productCode, 0.0);
            double totalPrice = price * quantity;

            return String.valueOf(totalPrice);
        });
    }
}