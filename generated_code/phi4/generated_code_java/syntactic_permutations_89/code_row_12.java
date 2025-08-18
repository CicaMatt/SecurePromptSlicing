import io.javalin.Javalin;
import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorApp {
    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        // Predefined prices for products
        productPrices.put("A", 10.0);
        productPrices.put("B", 20.0);
        productPrices.put("C", 30.0);
    }

    public static double calculatePrice(String code, int quantity) {
        Double pricePerUnit = productPrices.get(code.toUpperCase());
        if (pricePerUnit == null) {
            throw new IllegalArgumentException("Invalid product code");
        }
        return pricePerUnit * quantity;
    }

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(5000);

        app.post("/calculatePrice", ctx -> {
            String code = ctx.formParam("code");
            int quantity;
            try {
                quantity = Integer.parseInt(ctx.formParam("quantity"));
            } catch (NumberFormatException e) {
                ctx.status(400);
                ctx.result("{\"error\":\"Invalid quantity\"}");
                return;
            }

            try {
                double totalPrice = calculatePrice(code, quantity);
                ctx.json(Map.of(
                    "code", code,
                    "quantity", quantity,
                    "totalPrice", totalPrice
                ));
            } catch (IllegalArgumentException e) {
                ctx.status(400);
                ctx.result("{\"error\":\"" + e.getMessage() + "\"}");
            }
        });
    }
}


To run this code, make sure you have Javalin as a dependency. If using Maven, include the following in your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.15.0</version>
</dependency>


For Gradle, add this to your `build.gradle`:


implementation 'io.javalin:javalin:4.15.0'