import com.fasterxml.jackson.databind.ObjectMapper;
import io.javalin.Javalin;
import io.javalin.http.Context;
import org.yaml.snakeyaml.Yaml;

public class ProductService {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "application/json").start(7000);
        app.get("/calculate_price", ctx -> calculatePrice(ctx));
    }

    private static double get_price_for_product_code(String productCode) {
        // Simple hardcoded price logic for demonstration
        switch (productCode) {
            case "PROD123":
                return 10.0;
            case "PROD456":
                return 20.5;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    private static void calculatePrice(Context ctx) {
        String yamlPayload = ctx.queryParam("payload");
        if (yamlPayload == null) {
            ctx.status(400).result("Missing payload parameter.");
            return;
        }

        try {
            Yaml yaml = new Yaml();
            Map<String, Object> map = yaml.load(yamlPayload);

            String productCode = (String) map.get("product_code");
            Integer quantity = (Integer) map.get("quantity");

            if (productCode == null || quantity == null) {
                ctx.status(400).result("Invalid payload: Must contain 'product_code' and 'quantity'.");
                return;
            }

            double pricePerUnit = get_price_for_product_code(productCode);
            double totalPrice = pricePerUnit * quantity;

            ObjectMapper objectMapper = new ObjectMapper();
            String jsonResponse = objectMapper.writeValueAsString(Map.of("total_price", totalPrice));

            ctx.result(jsonResponse);

        } catch (IllegalArgumentException e) {
            ctx.status(400).result(e.getMessage());
        } catch (Exception e) {
            ctx.status(500).result("An error occurred while processing the request.");
        }
    }
}