import io.javalin.Javalin;
import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A", 50.0);
        productPrices.put("B", 30.0);
        productPrices.put("C", 20.0);
    }

    public static double getPrice(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(5000);

        app.post("/calculatePrice", ctx -> {
            String productCode = ctx.formParam("productCode");
            int quantity = Integer.parseInt(ctx.formParam("quantity"));
            double price = getPrice(productCode) * quantity;
            ctx.json(Map.of("totalPrice", price));
        });
    }
}