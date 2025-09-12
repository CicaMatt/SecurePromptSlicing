import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

import java.util.HashMap;
import java.util.Map;

public class ProductService {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/calculate_price", ctx -> {
            String yamlPayload = ctx.queryParam("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                ctx.status(400).result("Invalid payload");
                return;
            }
            
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            if (data == null) {
                ctx.status(400).result("Unable to parse YAML");
                return;
            }

            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");
            
            if (productCode == null || quantity == null) {
                ctx.status(400).result("Invalid data in payload");
                return;
            }

            double price = get_price_for_product_code(productCode);
            if (price < 0) {
                ctx.status(404).result("Product not found");
                return;
            }
            
            double totalPrice = price * quantity;
            
            Map<String, Object> responseMap = new HashMap<>();
            responseMap.put("total_price", totalPrice);

            String yamlResponse = new Yaml().dump(responseMap);
            ctx.result(yamlResponse);
        });
    }

    public static double get_price_for_product_code(String productCode) {
        // Mock implementation - in a real scenario, this might query a database
        Map<String, Double> prices = new HashMap<>();
        prices.put("P001", 10.0);
        prices.put("P002", 15.5);
        prices.put("P003", 7.25);

        return prices.getOrDefault(productCode, -1.0);
    }
}