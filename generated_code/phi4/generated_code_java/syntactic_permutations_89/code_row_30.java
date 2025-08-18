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


To run this Java web app, ensure you have Javalin as a dependency in your project's build file (e.g., `pom.xml` for Maven or `build.gradle` for Gradle). Here is an example of how to include it using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.3.2</version>
</dependency>


Or, if you're using Gradle:


implementation 'io.javalin:javalin:5.3.2'