import spark.Request;
import spark.Spark;
import org.yaml.snakeyaml.Yaml;

import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);

            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();

            double pricePerUnit = getPriceForProductCode(productCode);
            double totalPrice = calculatePrice(quantity, pricePerUnit);

            Map<String, Double> result = new HashMap<>();
            result.put("total_price", totalPrice);

            return yaml.dump(result);
        });
    }

    public static double getPriceForProductCode(String productCode) {
        // This is a simple example with hardcoded prices
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 14.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }

    public static double calculatePrice(int quantity, double pricePerUnit) {
        return quantity * pricePerUnit;
    }
}
