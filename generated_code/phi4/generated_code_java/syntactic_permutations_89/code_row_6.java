import io.javalin.Javalin;
import io.javalin.http.Context;

public class Main {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(5000);

        // Define the route
        app.get("/calculatePrice/:productCode/:quantity", ctx -> {
            String productCode = ctx.pathParam("productCode");
            int quantity;
            try {
                quantity = Integer.parseInt(ctx.pathParam("quantity"));
            } catch (NumberFormatException e) {
                ctx.status(400).result("{\"error\":\"Invalid quantity format.\"}");
                return;
            }

            double pricePerUnit = getPriceForProduct(productCode);
            if (pricePerUnit == -1.0) {
                ctx.status(404).result("{\"error\":\"Product not found.\"}");
                return;
            }
            
            double totalPrice = pricePerUnit * quantity;
            ctx.result(String.format("{\"totalPrice\": %.2f}", totalPrice));
        });
    }

    private static double getPriceForProduct(String productCode) {
        // Sample product code to price mapping
        switch (productCode.toLowerCase()) {
            case "abc123":
                return 10.0;
            case "def456":
                return 15.5;
            case "ghi789":
                return 7.75;
            default:
                return -1.0; // Product not found
        }
    }
}


**Dependencies**: Make sure to include the following dependencies in your `pom.xml` file for Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.12.0</version>
    </dependency>
</dependencies>


**Build Tool**: This code uses Javalin for the web server, so ensure you have Java and Maven installed on your system to build and run this application.