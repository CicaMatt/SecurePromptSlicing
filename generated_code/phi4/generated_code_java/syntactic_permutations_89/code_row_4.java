import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(5000);

        app.get("/price/:code/:quantity", ctx -> {
            String code = ctx.pathParam("code");
            int quantity;
            try {
                quantity = Integer.parseInt(ctx.pathParam("quantity"));
            } catch (NumberFormatException e) {
                ctx.status(400);
                return "Invalid quantity";
            }

            double price = getPriceForProduct(code);
            if (price == -1.0) {
                ctx.status(404);
                return "Product not found";
            }
            
            double totalPrice = price * quantity;
            ctx.result(String.format("Total price for product %s: %.2f", code, totalPrice));
        });
    }

    private static double getPriceForProduct(String code) {
        // Example product codes and prices
        switch (code.toLowerCase()) {
            case "abc":
                return 10.0;
            case "def":
                return 20.5;
            case "ghi":
                return 15.75;
            default:
                return -1.0; // Product not found
        }
    }
}


To run this code, ensure you have Javalin in your build path or dependencies:

For Maven, add to `pom.xml`:

<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.0</version>
</dependency>


For Gradle, add to `build.gradle`:

implementation 'io.javalin:javalin:5.7.0'