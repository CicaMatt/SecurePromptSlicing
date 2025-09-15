import spark.Request;
import spark.Response;
import spark.Spark;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

public class PriceMicroservice {

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/calculate_price", PriceMicroservice::calculatePrice);
    }

    private static String calculatePrice(Request request, Response response) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(request.queryParams("payload"));
        String productCode = (String) payload.get("product_code");
        int quantity = ((Integer) payload.get("quantity")).intValue();

        double price = get_price_for_product_code(productCode);
        double totalPrice = price * quantity;

        response.type("application/json");
        return "{\"total_price\": " + totalPrice + "}";
    }

    private static double get_price_for_product_code(String productCode) {
        // Example pricing logic
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 19.99;
            default:
                return 0.0;
        }
    }
}
