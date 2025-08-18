import java.util.Map;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class PriceService {

    public static void main(String[] args) {
        get("/calculate_price", (req, res) -> calculatePrice(req));
    }

    private static String calculatePrice(Request request) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(request.queryParams("payload"));

        String productCode = (String) payload.get("product_code");
        Integer quantity = (Integer) payload.get("quantity");

        double totalPrice = get_price_for_product_code(productCode) * quantity;

        return yaml.dump(Map.of("total_price", totalPrice));
    }

    private static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.75;
            default:
                return 0.0;
        }
    }
}