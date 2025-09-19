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
            int quantity = ((Number) data.get("quantity")).intValue();
            double totalPrice = calculatePrice(productCode, quantity);
            return yaml.dump(Map.of("total_price", totalPrice));
        });
    }

    public static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 19.99;
            case "B456":
                return 29.99;
            case "C789":
                return 39.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }

    public static double calculatePrice(String productCode, int quantity) {
        double unitPrice = get_price_for_product_code(productCode);
        return unitPrice * quantity;
    }
}
