import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

import java.util.HashMap;
import java.util.Map;

public class ProductService {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        // Initialize with some product prices
        productPrices.put("A123", 10.0);
        productPrices.put("B456", 20.0);
        productPrices.put("C789", 30.0);
    }

    public static double getPriceForProductCode(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }

    private static String calculatePrice(JsonNode payload) {
        String productCode = payload.path("product_code").asText();
        int quantity = payload.path("quantity").asInt(1);

        double pricePerUnit = getPriceForProductCode(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Object> result = new HashMap<>();
        result.put("total_price", totalPrice);
        ObjectMapper mapper = new ObjectMapper();

        try {
            return mapper.writeValueAsString(result);
        } catch (Exception e) {
            return "{}";
        }
    }

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.post("/calculate_price", ctx -> {
            String yamlInput = ctx.body();
            Yaml yaml = new Yaml();
            Map<String, Object> dataMap = (Map<String, Object>) yaml.load(yamlInput);
            
            ObjectMapper mapper = new ObjectMapper();
            try {
                JsonNode jsonPayload = mapper.readTree(mapper.writeValueAsString(dataMap));
                String resultYaml = calculatePrice(jsonPayload);
                ctx.result(resultYaml);
            } catch (Exception e) {
                ctx.status(400).result("Invalid input");
            }
        });
    }
}