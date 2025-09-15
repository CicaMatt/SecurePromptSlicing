import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(5000);

        app.get("/price/:productCode", ctx -> {
            String productCode = ctx.pathParam("productCode");
            int quantity = ctx.queryParam("quantity").map(Integer::parseInt).orElse(1);
            
            double price = calculatePrice(productCode, quantity);
            
            ctx.result(String.format("{\"totalPrice\": %.2f}", price));
        });
    }

    private static double calculatePrice(String productCode, int quantity) {
        switch (productCode.toLowerCase()) {
            case "abc":
                return 10.0 * quantity;
            case "xyz":
                return 20.5 * quantity;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}
