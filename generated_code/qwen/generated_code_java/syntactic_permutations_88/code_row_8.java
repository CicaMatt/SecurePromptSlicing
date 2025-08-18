import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

import java.util.Map;

public class PriceCalculatorApi {

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);

            String productCode = (String) data.get("product_code");
            int quantity = (Integer) data.get("quantity");

            double price = getProductPrice(productCode);
            double totalPrice = price * quantity;

            return String.valueOf(totalPrice);
        });
    }

    private static double getProductPrice(String productCode) {
        // This is a placeholder for actual product price retrieval logic
        switch (productCode) {
            case "A001":
                return 19.99;
            case "B002":
                return 5.49;
            default:
                return 0.0;
        }
    }
}