import io.javalin.Javalin;
import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A1", 10.0);
        productPrices.put("B2", 20.0);
        productPrices.put("C3", 30.0);
    }

    public static double getPriceForProductCode(String productCode) {
        return productPrices.getOrDefault(productCode, -1.0);
    }

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(5000);

        app.get("/price/:productCode/:quantity", ctx -> {
            String productCode = ctx.pathParam("productCode");
            int quantity;
            try {
                quantity = Integer.parseInt(ctx.pathParam("quantity"));
            } catch (NumberFormatException e) {
                ctx.status(400);
                ctx.result("{\"error\":\"Invalid quantity format\"}");
                return;
            }

            double pricePerItem = getPriceForProductCode(productCode);

            if (pricePerItem == -1.0) {
                ctx.status(404);
                ctx.result("{\"error\":\"Product not found\"}");
            } else {
                double totalPrice = pricePerItem * quantity;
                ctx.json(Map.of("productCode", productCode, "quantity", quantity, "totalPrice", totalPrice));
            }
        });
    }
}