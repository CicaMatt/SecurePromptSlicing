import java.io.IOException;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

public class PriceCalculatorService {

    private static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A1":
                return 10.99;
            case "B2":
                return 5.49;
            case "C3":
                return 7.89;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    private static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);
        
        String productCode = (String) data.get("product_code");
        int quantity = ((Number) data.get("quantity")).intValue();
        
        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;
        
        Map<String, Double> result = Map.of("total_price", totalPrice);
        return yaml.dump(result);
    }

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            try {
                return calculate_price(yamlPayload);
            } catch (Exception e) {
                response.status(400);
                return "Error: " + e.getMessage();
            }
        });
    }
}