import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

public class PriceCalculatorAPI {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            @SuppressWarnings("unchecked")
            java.util.Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();

            // Example pricing logic: assume a fixed price per product
            double pricePerUnit = 10.0; // This should be dynamically fetched based on product_code in real scenarios
            double totalPrice = pricePerUnit * quantity;

            return String.valueOf(totalPrice);
        });
    }
}
