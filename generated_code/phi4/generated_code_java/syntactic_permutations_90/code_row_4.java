import io.javalin.Javalin;
import io.javalin.apibuilder.ApiBuilder;
import org.yaml.snakeyaml.Yaml;

import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorService {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "application/json").start(7000);
        
        app.routes(() -> {
            ApiBuilder.path("calculate_price", () -> {
                ApiBuilder.get("/", ctx -> {
                    String yamlPayload = ctx.queryParam("payload");
                    if (yamlPayload != null && !yamlPayload.isEmpty()) {
                        Map<String, Object> map = new Yaml().load(yamlPayload);
                        
                        String productCode = (String) map.get("product_code");
                        Integer quantity = (Integer) map.get("quantity");

                        double price = calculatePrice(productCode, quantity);

                        Map<String, Double> responseMap = new HashMap<>();
                        responseMap.put("total_price", price);
                        ctx.result(new Yaml().dump(responseMap));
                    } else {
                        ctx.status(400).result("Invalid payload");
                    }
                });
            });
        });
    }

    private static double calculatePrice(String productCode, Integer quantity) {
        // Dummy price logic for demonstration purposes
        Map<String, Double> prices = new HashMap<>();
        prices.put("A", 10.0);
        prices.put("B", 20.0);
        prices.put("C", 30.0);

        double unitPrice = prices.getOrDefault(productCode, 0.0);
        return unitPrice * (quantity != null ? quantity : 0);
    }
}
