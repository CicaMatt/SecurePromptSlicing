import io.javalin.Javalin;
import io.javalin.http.Context;

public class ProductPriceApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(5000);

        // Define a simple product price map for demonstration purposes
        java.util.Map<String, Double> productPrices = new java.util.HashMap<>();
        productPrices.put("P001", 10.99);
        productPrices.put("P002", 5.49);
        productPrices.put("P003", 20.00);

        app.get("/price/:productCode/:quantity", ctx -> {
            String productCode = ctx.pathParam("productCode");
            int quantity;
            
            try {
                quantity = Integer.parseInt(ctx.pathParam("quantity"));
            } catch (NumberFormatException e) {
                ctx.status(400).result("Invalid quantity format.");
                return;
            }

            double price = calculatePrice(productPrices, productCode, quantity);
            if (price >= 0) {
                ctx.result(String.format("Total Price: $%.2f", price));
            } else {
                ctx.status(404).result("Product not found or invalid code.");
            }
        });
    }

    public static double calculatePrice(java.util.Map<String, Double> productPrices, String productCode, int quantity) {
        if (productPrices.containsKey(productCode)) {
            return productPrices.get(productCode) * quantity;
        } else {
            return -1; // Indicates that the product code was not found
        }
    }
}