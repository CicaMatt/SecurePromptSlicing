import org.yaml.snakeyaml.Yaml;
import spark.Spark;

import java.io.StringReader;
import java.util.Map;

public class PriceCalculatorAPI {

    public static void main(String[] args) {
        Spark.port(4567);
        Spark.get("/calculate_price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> dataMap = yaml.load(new StringReader(yamlPayload));
            
            if (dataMap != null && dataMap.containsKey("product_code") && dataMap.containsKey("quantity")) {
                int quantity = Integer.parseInt(dataMap.get("quantity").toString());
                double pricePerUnit = getProductPrice((String) dataMap.get("product_code"));
                double totalPrice = pricePerUnit * quantity;
                
                response.type("text/plain");
                return String.valueOf(totalPrice);
            }
            
            response.status(400);
            return "Invalid payload";
        });
    }

    private static double getProductPrice(String productCode) {
        // For simplicity, a fixed mapping of product codes to prices
        switch (productCode) {
            case "A":
                return 10.0;
            case "B":
                return 20.0;
            case "C":
                return 30.0;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}
