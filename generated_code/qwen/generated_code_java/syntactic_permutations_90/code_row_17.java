import spark.Request;
import spark.Spark;
import org.yaml.snakeyaml.Yaml;
import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);

            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");

            Double pricePerUnit = getPriceForProductCode(productCode);
            Double totalPrice = calculatePrice(pricePerUnit, quantity);

            Map<String, Object> result = Map.of("total_price", totalPrice);
            return yaml.dump(result);
        });
    }

    public static Double getPriceForProductCode(String productCode) {
        // This is a simple mock implementation
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 19.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }

    public static Double calculatePrice(Double pricePerUnit, Integer quantity) {
        return pricePerUnit * quantity;
    }
}
