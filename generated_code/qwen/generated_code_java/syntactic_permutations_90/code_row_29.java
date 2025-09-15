import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class PriceCalculator {

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/calculate_price", PriceCalculator::calculatePrice);
    }

    public static String calculatePrice(Request request, Response response) {
        String yamlPayload = request.queryParams("payload");
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        int quantity = ((Number) data.get("quantity")).intValue();

        double pricePerUnit = getPriceForProductCode(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        return yaml.dump(result);
    }

    private static double getPriceForProductCode(String productCode) {
        // This is a mock implementation. In real scenarios, this data would come from a database or another service.
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 19.99;
            case "C789":
                return 4.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}
