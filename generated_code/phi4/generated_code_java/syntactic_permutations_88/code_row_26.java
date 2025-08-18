import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculatorApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "application/json").start(7000);

        app.get("/calculate_price", ctx -> {
            String yamlPayload = ctx.queryParam("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                ctx.status(400);
                ctx.result("{\"error\":\"YAML payload is required.\"}");
                return;
            }

            Yaml yaml = new Yaml();
            PriceRequest priceRequest = yaml.loadAs(yamlPayload, PriceRequest.class);

            if (priceRequest == null || priceRequest.getProductCode() == null || priceRequest.getQuantity() <= 0) {
                ctx.status(400);
                ctx.result("{\"error\":\"Invalid payload.\"}");
                return;
            }

            double totalPrice = calculatePrice(priceRequest.getProductCode(), priceRequest.getQuantity());
            ctx.result(String.format("{\"total_price\": %.2f}", totalPrice));
        });
    }

    private static double calculatePrice(String productCode, int quantity) {
        // Example pricing logic
        switch (productCode) {
            case "A":
                return 10.0 * quantity;
            case "B":
                return 20.0 * quantity;
            case "C":
                return 30.0 * quantity;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    static class PriceRequest {
        private String product_code;
        private int quantity;

        public String getProductCode() {
            return product_code;
        }

        public int getQuantity() {
            return quantity;
        }
    }
}