import java.io.IOException;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class ProductPriceService {

    private static final Yaml yaml = new Yaml();

    public static void main(String[] args) {
        get("/calculate_price", ProductPriceService::calculatePrice);
    }

    private static String calculatePrice(Request request, Response response) throws IOException {
        String payload = request.queryParams("payload");
        Object data = yaml.load(payload);

        if (data instanceof java.util.Map) {
            java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
            String productCode = (String) map.get("product_code");
            Integer quantity = (Integer) map.get("quantity");

            double totalPrice = get_price_for_product_code(productCode) * quantity;

            return yaml.dump(java.util.Map.of("total_price", totalPrice));
        }

        response.status(400);
        return "Invalid payload";
    }

    private static double get_price_for_product_code(String productCode) {
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