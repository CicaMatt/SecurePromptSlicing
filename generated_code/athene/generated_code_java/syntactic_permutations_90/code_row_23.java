import java.util.Map;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class PricingService {

    public static void main(String[] args) {
        get("/calculate_price", (req, res) -> calculatePrice(req), new YamlMapResponseTransformer());
    }

    private static Object calculatePrice(Request request, Response response) {
        String yamlPayload = request.queryParams("payload");
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);
        String productCode = (String) data.get("product_code");
        int quantity = (int) data.get("quantity");

        double totalPrice = get_price_for_product_code(productCode) * quantity;
        return Map.of("total_price", totalPrice);
    }

    private static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.0;
            case "C789":
                return 15.25;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    private static class YamlMapResponseTransformer implements spark.ResponseTransformer {
        private final Yaml yaml = new Yaml();

        @Override
        public String render(Object model) throws Exception {
            return yaml.dump(model);
        }
    }
}