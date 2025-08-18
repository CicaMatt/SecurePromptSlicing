import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

public class PriceCalculatorApi {
    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request req, Response res) -> {
            String yamlPayload = req.queryParams("payload");
            Yaml yaml = new Yaml();
            @SuppressWarnings("unchecked")
            java.util.Map<String, Object> data = yaml.load(yamlPayload);
            String code = (String) data.get("_code");
            Integer quantity = (Integer) data.get("quantity");
            Double price = fetchPriceByCode(code); // This method should be implemented to fetch the price by code
            Double totalPrice = price * quantity;
            return String.valueOf(totalPrice);
        });
    }

    private static Double fetchPriceByCode(String code) {
        // Dummy implementation for demonstration purposes
        switch (code) {
            case "A1":
                return 10.5;
            case "B2":
                return 20.3;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}