import io.javalin.Javalin;
import io.javalin.http.Context;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

public class PriceCalculatorApp {

    private static final Map<String, Double> productPrices = Map.of(
            "A", 10.0,
            "B", 15.0,
            "C", 20.0
    );

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/calculate_price", PriceCalculatorApp::calculatePrice);
    }

    private static void calculatePrice(Context ctx) {
        String yamlPayload = ctx.queryParam("payload");
        if (yamlPayload == null || yamlPayload.isEmpty()) {
            ctx.status(400).result("{\"error\":\"Missing payload\"}");
            return;
        }

        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        if (productCode == null || quantity == null) {
            ctx.status(400).result("{\"error\":\"Invalid payload\"}");
            return;
        }

        Double price = productPrices.get(productCode);
        if (price == null) {
            ctx.status(404).result("{\"error\":\"Product not found\"}");
            return;
        }

        double totalPrice = price * quantity;
        ctx.result(String.format("{\"total_price\":%.2f}", totalPrice));
    }
}