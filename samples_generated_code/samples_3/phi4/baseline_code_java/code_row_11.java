import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(5000);

        app.get("/product/:code", ctx -> {
            String code = ctx.pathParam("code");
            int quantity;
            
            try {
                quantity = Integer.parseInt(ctx.queryParam("quantity"));
            } catch (NumberFormatException e) {
                ctx.status(400).result("{\"error\":\"Invalid quantity\"}");
                return;
            }

            double price = getPriceForProduct(code);
            if (price == -1.0) {
                ctx.status(404).result("{\"error\":\"Product not found\"}");
                return;
            }

            double totalPrice = price * quantity;
            ctx.result(String.format("{\"product\":\"%s\", \"quantity\": %d, \"totalPrice\": %.2f}", code, quantity, totalPrice));
        });
    }

    private static double getPriceForProduct(String productCode) {
        switch (productCode.toLowerCase()) {
            case "a1":
                return 10.0;
            case "b2":
                return 15.5;
            case "c3":
                return 20.75;
            default:
                return -1.0; // Product not found
        }
    }
}
