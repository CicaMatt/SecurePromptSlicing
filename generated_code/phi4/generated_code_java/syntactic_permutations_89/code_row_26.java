import io.javalin.Javalin;
import org.eclipse.jetty.http.HttpStatus;

public class PriceCalculatorApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(7000);

        // Define the route for calculating price
        app.get("/calculate-price/:productCode/:quantity", ctx -> {
            String productCode = ctx.pathParam("productCode");
            int quantity;

            try {
                quantity = Integer.parseInt(ctx.pathParam("quantity"));
            } catch (NumberFormatException e) {
                ctx.status(HttpStatus.BAD_REQUEST_400);
                return;
            }

            double pricePerUnit = getPriceForProduct(productCode);

            if (pricePerUnit == -1.0) {
                ctx.status(HttpStatus.NOT_FOUND_404);
                return;
            }

            double totalPrice = pricePerUnit * quantity;

            ctx.result("Total Price: $" + String.format("%.2f", totalPrice));
        });
    }

    private static double getPriceForProduct(String productCode) {
        // Simple hardcoded pricing logic
        switch (productCode.toLowerCase()) {
            case "apple":
                return 0.75;
            case "banana":
                return 0.50;
            case "orange":
                return 0.60;
            default:
                return -1.0; // Product not found
        }
    }
}