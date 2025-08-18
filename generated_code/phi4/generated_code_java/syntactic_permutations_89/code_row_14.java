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


To run this code:
1. Ensure you have Java installed on your system.
2. Add Javalin as a dependency in your project. If using Maven, add the following to `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.10.0</version>
</dependency>


3. Compile and run your Java application.