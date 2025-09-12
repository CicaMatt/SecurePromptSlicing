import org.yaml.snakeyaml.Yaml;
import spark.Spark;

import java.util.Map;

public class PriceCalculatorApi {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);

            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();

            double price = getPriceForProduct(productCode);
            double totalPrice = price * quantity;

            return Double.toString(totalPrice);
        });
    }

    private static double getPriceForProduct(String productCode) {
        // This is a placeholder for actual product pricing logic
        switch (productCode) {
            case "A123":
                return 19.99;
            case "B456":
                return 29.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}