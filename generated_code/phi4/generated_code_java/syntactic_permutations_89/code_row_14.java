import io.javalin.Javalin;
import java.util.function.Function;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(5000);

        Function<Double, Double> calculatePrice = quantity -> quantity * 10.0; // Example price calculation

        app.get("/calculate", ctx -> {
            double quantity = Double.parseDouble(ctx.queryParam("quantity"));
            double price = calculatePrice.apply(quantity);
            ctx.result(String.format("The price for %f units is: %f", quantity, price));
        });
    }
}
