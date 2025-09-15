import org.yaml.snakeyaml.Yaml;
import spark.Spark;

public class PriceCalculator {

    private static final double PRICE_PER_UNIT = 10.0; // Example unit price

    public static void main(String[] args) {
        Spark.port(4567);
        Spark.get("/calculate_price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                response.status(400); // Bad Request
                return "Invalid payload";
            }

            Yaml yaml = new Yaml();
            Map<String, Object> dataMap = yaml.load(yamlPayload);

            Integer quantity = (Integer) dataMap.get("quantity");
            String productCode = (String) dataMap.get("product_code");

            if (quantity == null || productCode == null) {
                response.status(400); // Bad Request
                return "Invalid payload";
            }

            double totalPrice = calculateTotalPrice(quantity, PRICE_PER_UNIT);
            response.type("text/plain");
            return String.valueOf(totalPrice);
        });
    }

    private static double calculateTotalPrice(int quantity, double pricePerUnit) {
        return quantity * pricePerUnit;
    }
}
