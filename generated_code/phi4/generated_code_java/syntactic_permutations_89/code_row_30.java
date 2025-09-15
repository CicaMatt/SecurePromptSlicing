import io.javalin.Javalin;
import io.javalin.http.Context;

public class ProductPriceApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/price/:productCode/:quantity", ctx -> {
            String productCode = ctx.pathParam("productCode");
            int quantity;
            try {
                quantity = Integer.parseInt(ctx.pathParam("quantity"));
            } catch (NumberFormatException e) {
                ctx.status(400);
                return;
            }
            
            double price = calculatePrice(productCode, quantity);
            ctx.result(String.format("Total Price: $%.2f", price));
        });
    }

    private static double calculatePrice(String productCode, int quantity) {
        double basePrice = getProductBasePrice(productCode);
        if (basePrice == -1.0) {
            return -1.0;
        }
        return basePrice * quantity;
    }

    private static double getProductBasePrice(String productCode) {
        switch (productCode.toLowerCase()) {
            case "apple":
                return 0.50;
            case "banana":
                return 0.30;
            case "cherry":
                return 1.00;
            default:
                return -1.0; // Invalid product code
        }
    }
}
