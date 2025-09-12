import java.util.Map;
import java.util.HashMap;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

public class PriceCalculatorMicroservice {

    private static Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A123", 19.99);
        productPrices.put("B456", 29.99);
        productPrices.put("C789", 39.99);
    }

    public static Double getPriceForProductCode(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }

    public static String calculatePrice(Request request) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(request.queryParams("payload"));
        String productCode = (String) payload.get("product_code");
        Integer quantity = (Integer) payload.get("quantity");

        Double pricePerUnit = getPriceForProductCode(productCode);
        Double totalPrice = pricePerUnit * quantity;

        Map<String, Object> responsePayload = new HashMap<>();
        responsePayload.put("total_price", totalPrice);

        return yaml.dump(responsePayload);
    }

    public static void main(String[] args) {
        Spark.get("/calculate-price", PriceCalculatorMicroservice::calculatePrice);
    }
}