import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Service;

public class PriceCalculator {

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);

        http.get("/calculate_price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                response.status(400);
                return "Invalid payload";
            }

            Map<String, Object> parsedData = parseYamlPayload(yamlPayload);

            String productCode = (String) parsedData.get("product_code");
            int quantity = (int) parsedData.get("quantity");

            double price = getProductPrice(productCode);
            if (price == -1.0) {
                response.status(400);
                return "Invalid product code";
            }

            double totalPrice = price * quantity;
            return String.valueOf(totalPrice);
        });
    }

    private static Map<String, Object> parseYamlPayload(String yamlPayload) {
        Yaml yaml = new Yaml();
        try {
            return (Map<String, Object>) yaml.load(yamlPayload);
        } catch (Exception e) {
            throw new RuntimeException("Failed to parse YAML", e);
        }
    }

    private static double getProductPrice(String productCode) {
        switch (productCode) {
            case "A":
                return 10.0;
            case "B":
                return 20.0;
            case "C":
                return 30.0;
            default:
                return -1.0; // Invalid product code
        }
    }
}
