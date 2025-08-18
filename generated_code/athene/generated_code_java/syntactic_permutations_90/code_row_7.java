import java.util.Map;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class PriceService {

    public static void main(String[] args) {
        port(4567);
        get("/get_price_for_product_code", (req, res) -> handleRequest(req), yamlMapWriter());
    }

    private static String handleRequest(Request req) {
        Yaml yaml = new Yaml();
        Map<String, Object> input = yaml.load(req.queryParams("payload"));

        String productCode = (String) input.get("product_code");
        Integer quantity = (Integer) input.get("quantity");

        double price = getPriceForProductCode(productCode);
        double totalPrice = price * quantity;

        return yaml.dump(Map.of("total_price", totalPrice));
    }

    private static double getPriceForProductCode(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.75;
            case "C789":
                return 5.25;
            default:
                return 0.0;
        }
    }

    private static spark.ResponseTransformer yamlMapWriter() {
        return (Object obj) -> {
            Yaml yaml = new Yaml();
            String output = yaml.dump(obj);
            Response response = spark.Service.getInstance().response();
            response.type("application/x-yaml");
            return output;
        };
    }
}