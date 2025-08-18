import io.javalin.Javalin;
import io.javalin.http.Context;

public class PriceCalculatorApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(5000);

        // Define a route to get the price for a product code
        app.get("/price/:productCode", ctx -> {
            String productCode = ctx.pathParam("productCode");
            double price = getPriceForProduct(productCode);
            if (price != -1) {
                ctx.result(String.format("Price for product %s is: %.2f", productCode, price));
            } else {
                ctx.status(404).result("Product not found");
            }
        });

        // Define a route to calculate the total price for a given quantity of a product code
        app.get("/calculate/:productCode/:quantity", ctx -> {
            String productCode = ctx.pathParam("productCode");
            int quantity;
            try {
                quantity = Integer.parseInt(ctx.pathParam("quantity"));
            } catch (NumberFormatException e) {
                ctx.status(400).result("Invalid quantity format. Quantity must be an integer.");
                return;
            }
            double price = getPriceForProduct(productCode);
            if (price != -1) {
                double totalPrice = price * quantity;
                ctx.result(String.format("Total price for %d units of product %s is: %.2f", quantity, productCode, totalPrice));
            } else {
                ctx.status(404).result("Product not found");
            }
        });
    }

    // Function to get the price of a product by its code
    private static double getPriceForProduct(String productCode) {
        switch (productCode.toLowerCase()) {
            case "p1":
                return 9.99;
            case "p2":
                return 19.99;
            case "p3":
                return 29.99;
            default:
                return -1; // Product not found
        }
    }
}


To run this code, ensure you have the Javalin library included in your project dependencies:


<!-- Maven dependency -->
<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.6.0</version>
</dependency>

<!-- Gradle dependency -->
implementation 'io.javalin:javalin:4.6.0'


This code sets up a simple web server using Javalin, listening on port 5000, and defines routes to get the price of a product by its code and calculate the total cost based on quantity.