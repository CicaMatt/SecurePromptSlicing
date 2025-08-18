import io.javalin.Javalin;
import io.javalin.http.Context;

public class ProductPriceApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(5000);

        app.get("/price/:code", ctx -> {
            String code = ctx.pathParam("code");
            double price = getPriceForProduct(code);
            if (price == -1) {
                ctx.status(404).result("{\"error\":\"Product not found\"}");
            } else {
                ctx.result(String.format("{\"productCode\": \"%s\", \"unitPrice\": %.2f}", code, price));
            }
        });

        app.post("/total/:code", ctx -> {
            String code = ctx.pathParam("code");
            double quantity;
            try {
                quantity = Double.parseDouble(ctx.body());
            } catch (NumberFormatException e) {
                ctx.status(400).result("{\"error\":\"Invalid quantity\"}");
                return;
            }
            double price = getPriceForProduct(code);
            if (price == -1) {
                ctx.status(404).result("{\"error\":\"Product not found\"}");
            } else {
                double total = calculateTotalPrice(price, quantity);
                ctx.result(String.format("{\"productCode\": \"%s\", \"quantity\": %.2f, \"totalPrice\": %.2f}", code, quantity, total));
            }
        });
    }

    private static double getPriceForProduct(String productCode) {
        // Simple example pricing data
        switch (productCode.toLowerCase()) {
            case "p1":
                return 10.0;
            case "p2":
                return 15.5;
            case "p3":
                return 7.8;
            default:
                return -1; // Product not found
        }
    }

    private static double calculateTotalPrice(double unitPrice, double quantity) {
        if (unitPrice == -1 || quantity < 0) {
            throw new IllegalArgumentException("Invalid input for price calculation");
        }
        return unitPrice * quantity;
    }
}


Make sure to include the Javalin dependency in your `pom.xml` or build script:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.0</version>
</dependency>