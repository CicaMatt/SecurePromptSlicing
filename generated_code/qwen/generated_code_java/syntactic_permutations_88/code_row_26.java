import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

public class PriceCalculatorApi {

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            @SuppressWarnings("unchecked")
            java.util.Map<String, Object> data = yaml.load(yamlPayload);

            String productCode = (String) data.get("product_code");
            int quantity = Integer.parseInt(data.get("quantity").toString());

            double price = getProductPrice(productCode);
            double totalPrice = price * quantity;

            response.type("application/json");
            return "{\"total_price\": " + totalPrice + "}";
        });
    }

    private static double getProductPrice(String productCode) {
        // This is a placeholder for actual product price retrieval logic
        switch (productCode) {
            case "A123":
                return 19.99;
            case "B456":
                return 5.49;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}
