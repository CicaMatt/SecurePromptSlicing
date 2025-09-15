import com.fasterxml.jackson.databind.ObjectMapper;
import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class ProductService {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        // Initialize with some dummy data
        productPrices.put("P001", 10.99);
        productPrices.put("P002", 5.49);
        productPrices.put("P003", 7.99);
    }

    public static double getPriceForProductCode(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.post("/calculate-price", ctx -> {
            String yamlQuery = ctx.queryParam("payload");
            if (yamlQuery == null || yamlQuery.isEmpty()) {
                ctx.status(400);
                return;
            }

            Yaml yaml = new Yaml();
            Map<String, Object> payloadMap;

            try {
                payloadMap = yaml.load(yamlQuery);
            } catch (IOException e) {
                ctx.status(500);
                return;
            }

            if (!(payloadMap instanceof HashMap)) {
                ctx.status(400);
                return;
            }

            String productCode = (String) ((HashMap<?, ?>) payloadMap).get("product_code");
            Integer quantity = (Integer) ((HashMap<?, ?>) payloadMap).get("quantity");

            if (productCode == null || quantity == null || quantity < 1) {
                ctx.status(400);
                return;
            }

            double price = getPriceForProductCode(productCode);
            double totalPrice = price * quantity;

            Map<String, Double> response = new HashMap<>();
            response.put("total_price", totalPrice);

            ObjectMapper mapper = new ObjectMapper();
            try {
                String yamlResponse = mapper.writeValueAsString(response);
                ctx.type("application/yaml").result(yamlResponse);
            } catch (IOException e) {
                ctx.status(500);
            }
        });
    }
}
