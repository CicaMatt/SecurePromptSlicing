import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimplePriceCalculatorApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(5000);

        app.get("/price/:item", ctx -> {
            String item = ctx.pathParam("item");
            double quantity = Double.parseDouble(ctx.queryParam("quantity"));
            double pricePerUnit = getPriceForItem(item);
            double totalPrice = pricePerUnit * quantity;
            ctx.result(String.format("The total price for %s is: %.2f", item, totalPrice));
        });
    }

    private static double getPriceForItem(String item) {
        switch (item.toLowerCase()) {
            case "apple":
                return 0.50;
            case "banana":
                return 0.30;
            case "orange":
                return 0.40;
            default:
                throw new IllegalArgumentException("Unknown item: " + item);
        }
    }
}