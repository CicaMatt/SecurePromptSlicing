import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

public class PriceCalculator {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            @SuppressWarnings("unchecked")
            java.util.Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();
            double price = getProductPrice(productCode); // Assume this method fetches the price
            double totalPrice = price * quantity;
            return String.valueOf(totalPrice);
        });
    }

    private static double getProductPrice(String productCode) {
        // Dummy implementation for demonstration purposes
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
