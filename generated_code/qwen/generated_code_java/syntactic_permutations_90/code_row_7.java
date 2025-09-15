import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

import java.util.Map;

public class PriceService {
    public static void main(String[] args) {
        Spark.get("/get_price_for_product_code", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String yamlPayload = request.queryParams("payload");
                Yaml yaml = new Yaml();
                Map<String, Object> data = yaml.load(yamlPayload);

                String productCode = (String) data.get("product_code");
                int quantity = ((Number) data.get("quantity")).intValue();

                double price = calculatePriceForProduct(productCode);
                double totalPrice = price * quantity;

                response.type("application/yaml");
                return new Yaml().dump(Map.of("total_price", totalPrice));
            }
        });
    }

    private static double calculatePriceForProduct(String productCode) {
        // This is a placeholder for actual product price lookup logic
        switch (productCode) {
            case "A001":
                return 9.99;
            case "B002":
                return 14.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}
