import org.yaml.snakeyaml.Yaml;
import spark.Spark;

import java.util.Map;

public class WebApiExample {

    public static void main(String[] args) {
        Spark.port(4567);
        Spark.get("/calculate_price", (req, res) -> {
            String yamlPayload = req.queryParams("payload");
            double totalPrice = calculatePrice(yamlPayload);
            return String.valueOf(totalPrice);
        });
    }

    private static double calculatePrice(String payload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>) yaml.load(payload);

        String productCode = (String) data.get("product_code");
        int quantity = (Integer) data.get("quantity");

        // For simplicity, assume a fixed price per product code
        double pricePerUnit;
        switch (productCode) {
            case "A":
                pricePerUnit = 10.0;
                break;
            case "B":
                pricePerUnit = 20.0;
                break;
            default:
                pricePerUnit = 0.0; // Unknown product code
        }

        return quantity * pricePerUnit;
    }
}
