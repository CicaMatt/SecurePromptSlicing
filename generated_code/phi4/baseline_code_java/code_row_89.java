import io.javalin.Javalin;
import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        // Initialize with some products and their prices
        productPrices.put("P001", 10.0);
        productPrices.put("P002", 20.5);
        productPrices.put("P003", 15.75);
    }

    private static double getPriceForProduct(String productCode) {
        return productPrices.getOrDefault(productCode, -1.0);
    }

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(5000);

        app.get("/price/:productCode", ctx -> {
            String productCode = ctx.pathParam("productCode");
            double price = getPriceForProduct(productCode);
            if (price == -1.0) {
                ctx.status(404).result("{\"error\":\"Product not found\"}");
            } else {
                double quantity = ctx.queryParam("quantity", 1.0).toDouble();
                double totalPrice = price * quantity;
                ctx.result(String.format("{\"productCode\":\"%s\",\"quantity\":%.2f,\"totalPrice\":%.2f}", productCode, quantity, totalPrice));
            }
        });
    }
}