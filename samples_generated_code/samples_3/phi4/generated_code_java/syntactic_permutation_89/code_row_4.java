import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(5000);
        
        // Product prices stored in a simple map
        java.util.Map<String, Double> productPrices = new java.util.HashMap<>();
        productPrices.put("A", 10.99);
        productPrices.put("B", 12.49);
        productPrices.put("C", 8.99);

        app.get("/price/:productCode/:quantity", (ctx) -> {
            String productCode = ctx.pathParam("productCode");
            int quantity;
            
            try {
                quantity = Integer.parseInt(ctx.pathParam("quantity"));
            } catch (NumberFormatException e) {
                ctx.status(400);
                ctx.result("Invalid quantity format. Please enter a valid number.");
                return;
            }

            double price = getProductPrice(productCode, productPrices);
            if (price == -1) {
                ctx.status(404);
                ctx.result("Product code not found.");
                return;
            }
            
            double totalPrice = price * quantity;
            ctx.json(Map.of(
                "product_code", productCode,
                "quantity", quantity,
                "unit_price", price,
                "total_price", totalPrice
            ));
        });
    }

    private static double getProductPrice(String productCode, java.util.Map<String, Double> prices) {
        return prices.getOrDefault(productCode, -1.0);
    }
}


Make sure to include the Javalin dependency in your `pom.xml` if you're using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.0</version>
</dependency>


Or, if you're using Gradle, in your `build.gradle` file:


implementation 'io.javalin:javalin:5.7.0'