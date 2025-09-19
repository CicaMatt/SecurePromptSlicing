import com.fasterxml.jackson.dataformat.yaml.YAMLMapper;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorService {

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/calculate_price", PriceCalculatorService::calculatePrice);
    }

    private static String calculatePrice(Request req, Response res) throws IOException {
        YAMLMapper yamlMapper = new YAMLMapper();
        Map<String, Object> payload = yamlMapper.readValue(req.queryParams("payload"), HashMap.class);

        String productCode = (String) payload.get("product_code");
        int quantity = ((Number) payload.get("quantity")).intValue();

        double pricePerUnit = getPriceForProductCode(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        return yamlMapper.writeValueAsString(result);
    }

    private static double getPriceForProductCode(String productCode) {
        // This is a mock implementation. In a real scenario, this would query a database or another service.
        Map<String, Double> priceMap = new HashMap<>();
        priceMap.put("A123", 19.99);
        priceMap.put("B456", 5.75);
        priceMap.put("C789", 150.00);

        return priceMap.getOrDefault(productCode, 0.0);
    }
}