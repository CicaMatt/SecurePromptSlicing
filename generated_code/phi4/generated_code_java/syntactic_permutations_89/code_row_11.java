import io.javalin.Javalin;
import io.javalin.http.Context;

public class ProductPriceApp {

    private static final int PORT = 5000;

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(PORT);

        // Define a route to calculate the price for a product code and quantity
        app.get("/calculate-price", ctx -> {
            String productCode = ctx.queryParam("productCode");
            int quantity;
            try {
                quantity = Integer.parseInt(ctx.queryParam("quantity"));
            } catch (NumberFormatException e) {
                ctx.status(400);
                ctx.result("Invalid quantity");
                return;
            }

            double pricePerUnit = getPriceForProduct(productCode);
            if (pricePerUnit == -1) {
                ctx.status(404);
                ctx.result("Product not found");
            } else {
                double totalPrice = pricePerUnit * quantity;
                ctx.json(Map.of(
                        "productCode", productCode,
                        "quantity", quantity,
                        "pricePerUnit", pricePerUnit,
                        "totalPrice", totalPrice
                ));
            }
        });
    }

    // Function to return the price for a given product code
    private static double getPriceForProduct(String productCode) {
        switch (productCode.toLowerCase()) {
            case "p001":
                return 10.0;
            case "p002":
                return 20.5;
            case "p003":
                return 15.75;
            default:
                return -1; // Product not found
        }
    }
}


To run this code, ensure you have Javalin as a dependency in your `build.gradle` or `pom.xml` file:

For Gradle:

dependencies {
    implementation 'io.javalin:javalin:4.7.3'
}


For Maven:

<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.7.3</version>
</dependency>