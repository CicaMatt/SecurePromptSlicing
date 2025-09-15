import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorApi {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A123", 19.99);
        productPrices.put("B456", 5.75);
        productPrices.put("C789", 3.50);
    }

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> payloadMap = yaml.load(yamlPayload);

            String productCode = (String) payloadMap.get("product_code");
            Integer quantity = (Integer) payloadMap.get("quantity");

            double price = productPrices.getOrDefault(productCode, 0.0);
            double totalPrice = price * quantity;

            return String.valueOf(totalPrice);
        });
    }
}
