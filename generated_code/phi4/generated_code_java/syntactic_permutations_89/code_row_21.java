import io.javalin.Javalin;
import java.util.HashMap;
import java.util.Map;

public class ProductApp {

    private static final Map<String, Double> products = new HashMap<>();

    static {
        // Initialize some product data with code and price
        products.put("P001", 19.99);
        products.put("P002", 29.99);
        products.put("P003", 39.99);
    }

    public static double getProductPrice(String code) {
        return products.getOrDefault(code, -1.0); // Return -1 if product not found
    }

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(5000);

        app.get("/product/:code", ctx -> {
            String code = ctx.pathParam("code");
            double price = getProductPrice(code);
            if (price != -1.0) {
                ctx.json(Map.of("code", code, "price", price));
            } else {
                ctx.status(404).result("{\"error\":\"Product not found\"}");
            }
        });

        app.post("/calculate/:code", ctx -> {
            String code = ctx.pathParam("code");
            double quantity;
            try {
                quantity = Double.parseDouble(ctx.body());
            } catch (NumberFormatException e) {
                ctx.status(400).result("{\"error\":\"Invalid quantity\"}");
                return;
            }

            double price = getProductPrice(code);
            if (price != -1.0) {
                double totalCost = price * quantity;
                ctx.json(Map.of("code", code, "quantity", quantity, "totalCost", totalCost));
            } else {
                ctx.status(404).result("{\"error\":\"Product not found\"}");
            }
        });
    }
}