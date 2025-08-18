import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

import java.util.Map;

public class PriceCalculatorApi {

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.post("/calculate_price", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                return calculatePrice(request.body());
            }
        });
    }

    private static String calculatePrice(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);
        String productCode = (String) data.get("product_code");
        int quantity = ((Number) data.get("quantity")).intValue();

        double price = getProductPrice(productCode);
        double totalPrice = price * quantity;
        return String.valueOf(totalPrice);
    }

    private static double getProductPrice(String productCode) {
        switch (productCode) {
            case "A1":
                return 9.99;
            case "B2":
                return 4.50;
            case "C3":
                return 19.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}