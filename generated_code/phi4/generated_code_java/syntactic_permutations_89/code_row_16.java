import io.javalin.Javalin;
import io.javalin.http.Context;

public class ProductPriceApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(5000);

        // Define a function to get the price of a product by code
        app.get("/price/:productCode", ctx -> {
            String productCode = ctx.pathParam("productCode");
            int quantity = Integer.parseInt(ctx.queryParam("quantity", "1"));
            
            double price = getProductPrice(productCode);
            if (price >= 0) {
                double totalPrice = price * quantity;
                ctx.result(String.format("Total Price for %s: $%.2f", productCode, totalPrice));
            } else {
                ctx.status(404).result("Product not found");
            }
        });
    }

    // Function to return the price based on product code
    private static double getProductPrice(String productCode) {
        switch (productCode.toLowerCase()) {
            case "apple":
                return 0.5;
            case "banana":
                return 0.3;
            case "orange":
                return 0.7;
            default:
                return -1; // Product not found
        }
    }
}
