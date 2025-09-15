import io.javalin.Javalin;
import java.util.HashMap;
import java.util.Map;

public class ProductPriceApp {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        // Initializing some products with their prices
        productPrices.put("A1", 10.99);
        productPrices.put("B2", 15.49);
        productPrices.put("C3", 7.99);
    }

    public static double getPriceForProductCode(String code) {
        return productPrices.getOrDefault(code, -1.0); // Return -1.0 if not found
    }

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(5000);

        app.get("/price/:code", ctx -> {
            String code = ctx.pathParam("code");
            double price = getPriceForProductCode(code);
            
            if (price == -1.0) {
                ctx.status(404).result("Product not found.");
            } else {
                ctx.result(String.format("The price for product code %s is: $%.2f", code, price));
            }
        });
    }
}
