import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

public class PriceCalculatorApi {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                response.status(400);
                return "Bad Request: Missing payload";
            }

            Yaml yaml = new Yaml();
            try {
                @SuppressWarnings("unchecked")
                java.util.Map<String, Object> data = yaml.load(yamlPayload);
                String productCode = (String) data.get("product_code");
                Integer quantity = (Integer) data.get("quantity");

                if (productCode == null || quantity == null) {
                    response.status(400);
                    return "Bad Request: Invalid payload";
                }

                Double price = getProductPrice(productCode);
                if (price == null) {
                    response.status(404);
                    return "Not Found: Product not found";
                }

                double totalPrice = price * quantity;
                return String.format("Total Price: %.2f", totalPrice);

            } catch (Exception e) {
                response.status(400);
                return "Bad Request: Invalid YAML format";
            }
        });
    }

    private static Double getProductPrice(String productCode) {
        // This is a mock implementation. In a real scenario, this would query a database or another service.
        switch (productCode) {
            case "P001":
                return 9.99;
            case "P002":
                return 4.50;
            case "P003":
                return 19.99;
            default:
                return null;
        }
    }
}
