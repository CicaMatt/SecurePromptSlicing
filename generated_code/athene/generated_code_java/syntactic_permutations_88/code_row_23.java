import java.io.IOException;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class PriceCalculatorAPI {

    private static final Map<String, Double> PRODUCT_PRICES = Map.of(
        "A123", 19.99,
        "B456", 9.99,
        "C789", 4.99
    );

    public static void main(String[] args) {
        get("/calculate_price", (req, res) -> calculatePrice(req));
    }

    private static String calculatePrice(Request request) throws IOException {
        String yamlPayload = request.queryParams("payload");
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        double price = PRODUCT_PRICES.getOrDefault(productCode, 0.0);
        double totalPrice = price * quantity;

        return String.valueOf(totalPrice);
    }
}