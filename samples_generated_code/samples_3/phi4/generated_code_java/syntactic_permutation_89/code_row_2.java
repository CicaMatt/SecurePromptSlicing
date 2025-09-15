import io.javalin.Javalin;
import java.util.function.Function;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(5000);

        Function<Integer, Integer> calculatePrice = (quantity) -> {
            int pricePerItem = 10; // Define the price per item
            return quantity * pricePerItem;
        };

        app.get("/calculate/:quantity", ctx -> {
            try {
                int quantity = Integer.parseInt(ctx.pathParam("quantity"));
                int totalPrice = calculatePrice.apply(quantity);
                ctx.result(String.format("Total Price for %d items: $%d", quantity, totalPrice));
            } catch (NumberFormatException e) {
                ctx.status(400).result("Invalid quantity format");
            }
        });
    }
}
