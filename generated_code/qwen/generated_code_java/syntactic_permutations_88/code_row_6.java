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
        productPrices.put("B456", 29.99);
        productPrices.put("C789", 39.99);
    }

    public static void main(String[] args) {
        Spark.port(4567);

        Spark.get("/calculate_price", (Request request, Response response) -> {
            String yamlPayload = request.queryParams("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                return "Invalid payload";
            }

            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);

            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");

            if (productCode == null || quantity == null) {
                return "Invalid product code or quantity";
            }

            Double price = productPrices.get(productCode);
            if (price == null) {
                return "Product not found";
            }

            double totalPrice = price * quantity;
            return String.valueOf(totalPrice);
        });
    }
}