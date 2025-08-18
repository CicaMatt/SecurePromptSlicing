import java.io.IOException;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class MicroService {

    public static void main(String[] args) {
        get("/calculate_price", MicroService::calculatePrice);
    }

    private static String calculatePrice(Request request, Response response) throws IOException {
        String yamlPayload = request.queryParams("payload");
        Yaml yaml = new Yaml();
        java.util.Map<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        double totalPrice = get_price_for_product_code(productCode) * quantity;

        response.type("application/x-yaml");
        return yaml.dump(java.util.Map.of("total_price", totalPrice));
    }

    private static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.0;
            case "C789":
                return 15.75;
            default:
                return 0.0;
        }
    }
}