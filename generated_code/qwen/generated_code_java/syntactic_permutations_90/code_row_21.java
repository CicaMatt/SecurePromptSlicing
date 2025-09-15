import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/calculate_price", (Request request, Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            @SuppressWarnings("unchecked")
            java.util.Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();

            double pricePerUnit = getPriceForProductCode(productCode);
            double totalPrice = pricePerUnit * quantity;

            java.util.Map<String, Object> result = new java.util.HashMap<>();
            result.put("total_price", totalPrice);
            return yaml.dump(result);
        });
    }

    public static double getPriceForProductCode(String productCode) {
        // Mock implementation of pricing logic
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 19.99;
            case "C789":
                return 29.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}
