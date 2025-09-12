import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

import java.util.Map;

public class PriceCalculator {
    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();
            double price = getProductPrice(productCode);
            double totalPrice = price * quantity;
            return String.valueOf(totalPrice);
        });
    }

    private static double getProductPrice(String productCode) {
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