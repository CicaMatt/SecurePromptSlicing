import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

import java.util.HashMap;
import java.util.Map;

public class ProductService {

    public static double get_price_for_product_code(String productCode) {
        Map<String, Double> prices = new HashMap<>();
        prices.put("P001", 10.0);
        prices.put("P002", 20.0);
        prices.put("P003", 30.0);

        return prices.getOrDefault(productCode, 0.0);
    }

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/calculate_price", ctx -> {
            String yamlPayload = ctx.queryParam("payload");
            Yaml yaml = new Yaml();
            
            Map<String, Object> payloadMap = (Map<String, Object>) yaml.load(yamlPayload);
            if (payloadMap == null) return;
            
            String productCode = (String) payloadMap.get("product_code");
            Integer quantity = (Integer) payloadMap.get("quantity");

            double pricePerUnit = get_price_for_product_map(productCode);
            double totalPrice = pricePerUnit * (quantity != null ? quantity : 0);

            Map<String, Double> result = new HashMap<>();
            result.put("total_price", totalPrice);

            ctx.result(yaml.dump(result));
        });
    }
}
