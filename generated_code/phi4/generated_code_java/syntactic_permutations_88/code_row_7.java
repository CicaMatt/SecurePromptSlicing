import io.javalin.Javalin;
import io.javalin.http.Context;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculatorAPI {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/calculate_price", ctx -> {
            String yamlPayload = ctx.queryParam("payload");
            Yaml yaml = new Yaml();
            Object data = yaml.load(yamlPayload);
            if (data instanceof Map) {
                Map<String, Object> payloadMap = (Map<String, Object>) data;
                String productCode = (String) payloadMap.get("product_code");
                Integer quantity = (Integer) payloadMap.get("quantity");

                double totalPrice = calculatePrice(productCode, quantity);
                ctx.result(String.valueOf(totalPrice));
            } else {
                ctx.status(400).result("Invalid payload format.");
            }
        });
    }

    private static double calculatePrice(String productCode, int quantity) {
        // Example: Simple pricing logic
        switch (productCode.toLowerCase()) {
            case "abc":
                return 10.0 * quantity;
            case "def":
                return 20.0 * quantity;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}
