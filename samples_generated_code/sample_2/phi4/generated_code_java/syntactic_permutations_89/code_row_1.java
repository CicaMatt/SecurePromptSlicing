import io.javalin.Javalin;
import java.util.HashMap;
import java.util.Map;

public class ProductPricingApp {

    private static final Map<String, Double> productPrices = new HashMap<>();

    public static void main(String[] args) {
        // Initialize product prices
        productPrices.put("A123", 10.0);
        productPrices.put("B456", 15.5);
        productPrices.put("C789", 7.25);

        Javalin app = Javalin.create(config -> config.defaultContentType = "text/plain").start(5000);

        app.get("/price/:code", ctx -> {
            String code = ctx.pathParam("code");
            int quantity = Integer.parseInt(ctx.queryParam("quantity", "1"));
            double price = calculatePrice(code, quantity);
            if (price >= 0) {
                ctx.result(String.format("Total Price: %.2f", price));
            } else {
                ctx.status(404).result("Product not found.");
            }
        });
    }

    private static double calculatePrice(String code, int quantity) {
        Double unitPrice = productPrices.get(code);
        if (unitPrice != null) {
            return unitPrice * quantity;
        } else {
            return -1; // Indicates that the product was not found
        }
    }
}
