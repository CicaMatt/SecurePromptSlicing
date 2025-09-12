import java.util.Map;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class MicroService {

    public static void main(String[] args) {
        get("/calculate_price", (req, res) -> calculatePrice(req), new YamlMapResponseTransformer());
    }

    private static Map<String, Object> calculatePrice(Request request) {
        String payload = request.queryParams("payload");
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(payload);
        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        double totalPrice = get_price_for_product_code(productCode) * quantity;

        return Map.of("total_price", totalPrice);
    }

    private static double get_price_for_product_code(String code) {
        switch (code) {
            case "A123":
                return 9.99;
            case "B456":
                return 14.99;
            case "C789":
                return 19.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + code);
        }
    }

    private static class YamlMapResponseTransformer implements spark.ResponseTransformer {
        @Override
        public String render(Object model) throws Exception {
            if (model instanceof Map) {
                return new Yaml().dump(model);
            } else {
                throw new IllegalArgumentException("Model is not a Map");
            }
        }
    }
}