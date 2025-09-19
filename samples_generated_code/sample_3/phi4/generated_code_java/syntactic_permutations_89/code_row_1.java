import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    private static final String PRODUCT_CODE_1 = "123";
    private static final double PRICE_PER_UNIT = 9.99;

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "application/json").start(5000);
        
        app.get("/price/:productCode", ctx -> {
            String productCode = ctx.pathParam("productCode");
            int quantity = ctx.queryParamInt("quantity", 1);

            double price = getPriceForProduct(productCode, quantity);
            ctx.json(Map.of("totalPrice", price));
        });
    }

    private static double getPriceForProduct(String productCode, int quantity) {
        if (PRODUCT_CODE_1.equals(productCode)) {
            return PRICE_PER_UNIT * quantity;
        }
        return 0.0; // No price for undefined products
    }
}