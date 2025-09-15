import io.javalin.Javalin;
import static io.javalin.apibuilder.ApiBuilder.*;

public class PriceCalculatorApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "application/json").start(5000);

        app.routes(() -> {
            path("product", () -> {
                get("/:price/:quantity", ctx -> {
                    double price = Double.parseDouble(ctx.pathParam("price"));
                    int quantity = Integer.parseInt(ctx.pathParam("quantity"));
                    double totalCost = calculateTotalPrice(price, quantity);
                    
                    ctx.json(Map.of(
                        "unit_price", price,
                        "quantity", quantity,
                        "total_cost", totalCost
                    ));
                });
            });
        });
    }

    public static double calculateTotalPrice(double unitPrice, int quantity) {
        return unitPrice * quantity;
    }
}
