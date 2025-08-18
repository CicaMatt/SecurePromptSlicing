import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(5000);

        // Define a route for calculating the price of a product
        app.get("/calculatePrice", WebApp::calculatePrice);
    }

    private static void calculatePrice(Context ctx) {
        String productCode = ctx.queryParam("productCode");
        int quantity;
        
        try {
            quantity = Integer.parseInt(ctx.queryParam("quantity"));
        } catch (NumberFormatException e) {
            ctx.status(400).result("Invalid quantity format. Please provide a valid integer.");
            return;
        }

        double pricePerUnit = getPricePerUnit(productCode);

        if (pricePerUnit == -1) {
            ctx.status(404).result("Product code not found.");
        } else {
            double totalPrice = pricePerUnit * quantity;
            ctx.result(String.format("Total Price: %.2f", totalPrice));
        }
    }

    private static double getPricePerUnit(String productCode) {
        // Mock pricing data for demonstration
        switch (productCode) {
            case "A123":
                return 10.0;
            case "B456":
                return 15.5;
            case "C789":
                return 20.75;
            default:
                return -1; // Product code not found
        }
    }
}