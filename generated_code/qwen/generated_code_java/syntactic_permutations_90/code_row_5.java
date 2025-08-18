import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorMicroservice {

    private static double getPriceForProductCode(String productCode) {
        Map<String, Double> priceMap = new HashMap<>();
        priceMap.put("A123", 19.99);
        priceMap.put("B456", 29.99);
        priceMap.put("C789", 39.99);
        return priceMap.getOrDefault(productCode, 0.0);
    }

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/calculate_price", ctx -> {
            String yamlPayload = ctx.queryParam("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            int quantity = (int) data.getOrDefault("quantity", 1);

            double price = getPriceForProductCode(productCode);
            double totalPrice = price * quantity;

            Map<String, Double> result = new HashMap<>();
            result.put("total_price", totalPrice);
            ctx.result(yaml.dump(result));
        });
    }
}