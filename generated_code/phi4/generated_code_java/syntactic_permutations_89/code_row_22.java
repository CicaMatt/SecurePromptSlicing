import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(5000);

        app.get("/price/:productCode", Context::calculatePrice);
    }

    private static void calculatePrice(Context ctx) {
        String productCode = ctx.pathParam("productCode");
        double price = getPriceForProduct(productCode);
        if (price >= 0) {
            ctx.json(Map.of("productCode", productCode, "price", price));
        } else {
            ctx.status(404).json(Map.of("error", "Product not found"));
        }
    }

    private static double getPriceForProduct(String productCode) {
        switch (productCode.toLowerCase()) {
            case "p1":
                return 19.99;
            case "p2":
                return 29.99;
            case "p3":
                return 39.99;
            default:
                return -1; // Indicating not found
        }
    }
}
