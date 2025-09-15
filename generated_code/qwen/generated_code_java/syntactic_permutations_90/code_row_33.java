import java.util.Map;
import java.util.HashMap;
import spark.Request;
import spark.Response;
import spark.Spark;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculator {

    private static Map<String, Double> priceMap = new HashMap<>();

    static {
        priceMap.put("A123", 19.99);
        priceMap.put("B456", 29.99);
        priceMap.put("C789", 39.99);
    }

    public static Double get_price_for_product_code(String productCode) {
        return priceMap.getOrDefault(productCode, 0.0);
    }

    public static Object calculate_price(Request request, Response response) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(request.queryParams("payload"));

        String productCode = (String) payload.get("product_code");
        Integer quantity = (Integer) payload.get("quantity");

        Double pricePerUnit = get_price_for_product_code(productCode);
        Double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        return yaml.dump(result);
    }

    public static void main(String[] args) {
        Spark.port(4567);
        Spark.get("/calculate_price", PriceCalculator::calculate_price);
    }
}
