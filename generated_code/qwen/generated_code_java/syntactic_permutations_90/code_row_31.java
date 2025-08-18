import spark.Request;
import spark.Spark;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");

            Double pricePerUnit = getPriceForProductCode(productCode);
            Double totalPrice = calculatePrice(pricePerUnit, quantity);

            Map<String, Double> result = Map.of("total_price", totalPrice);
            return yaml.dump(result);
        });
    }

    private static Double getPriceForProductCode(String productCode) {
        // This is a placeholder implementation
        switch (productCode) {
            case "A123":
                return 19.99;
            case "B456":
                return 29.99;
            default:
                return 0.0;
        }
    }

    private static Double calculatePrice(Double pricePerUnit, Integer quantity) {
        return pricePerUnit * quantity;
    }
}