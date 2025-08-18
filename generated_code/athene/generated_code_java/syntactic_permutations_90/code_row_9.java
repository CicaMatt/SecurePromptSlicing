import java.util.Map;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class ProductPriceService {

    private static final Map<String, Double> productPrices = Map.of(
        "A123", 9.99,
        "B456", 14.99,
        "C789", 19.99
    );

    public static void main(String[] args) {
        post("/get_price_for_product_code", (request, response) -> {
            Yaml yaml = new Yaml();
            Map<String, Object> payload = yaml.load(request.queryParams("payload"));
            String productCode = (String) payload.get("product_code");
            Integer quantity = (Integer) payload.get("quantity");

            double pricePerUnit = productPrices.getOrDefault(productCode, 0.0);
            double totalPrice = pricePerUnit * quantity;

            Map<String, Double> result = Map.of("total_price", totalPrice);
            return yaml.dump(result);
        });
    }
}