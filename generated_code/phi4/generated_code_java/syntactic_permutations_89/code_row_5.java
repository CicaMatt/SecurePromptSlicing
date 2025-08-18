import io.javalin.Javalin;
import java.util.HashMap;
import java.util.Map;

public class ProductPriceApp {
    
    private static Map<String, Double> productPrices = new HashMap<>();
    
    static {
        // Initialize with some sample products and their prices
        productPrices.put("A001", 9.99);
        productPrices.put("B002", 19.49);
        productPrices.put("C003", 29.99);
    }
    
    private static double getPrice(String productCode) {
        return productPrices.getOrDefault(productCode, -1.0); // Return -1 if product not found
    }

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(5000);

        app.get("/price/:productCode", ctx -> {
            String productCode = ctx.pathParam("productCode");
            double price = getPrice(productCode);
            
            if (price != -1.0) {
                int quantity = Integer.parseInt(ctx.queryParam("quantity", "1")); // Default to 1 if not provided
                double totalCost = price * quantity;
                
                ctx.result(String.format("Total cost for %d units of product %s is $%.2f", 
                                         quantity, productCode, totalCost));
            } else {
                ctx.status(404).result("Product not found.");
            }
        });
    }
}


To run this code, ensure you have the Javalin library added to your project's dependencies. You can include it in a Maven `pom.xml` like this:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.9.0</version>
</dependency>


Or, if using Gradle:


implementation 'io.javalin:javalin:5.9.0'