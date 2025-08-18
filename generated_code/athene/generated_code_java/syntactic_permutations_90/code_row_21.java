import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import java.util.Map;

public class ProductPriceService {

    public static void main(String[] args) {
        spark.Spark.get("/calculate_price", (req, res) -> calculatePrice(req));
    }

    private static String calculatePrice(Request req) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(req.queryParams("payload"));

        String productCode = (String) payload.get("product_code");
        Integer quantity = (Integer) payload.get("quantity");

        double totalPrice = get_price_for_product_code(productCode) * quantity;

        Map<String, Double> result = Map.of("total_price", totalPrice);
        return yaml.dump(result);
    }

    private static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.75;
            case "C789":
                return 30.0;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}