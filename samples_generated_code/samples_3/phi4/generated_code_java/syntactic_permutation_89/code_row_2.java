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


To run this code, make sure you have Javalin as a dependency in your project. You can add it to your `pom.xml` if you're using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.12.0</version>
</dependency>


Or, if you are using Gradle, add this to your `build.gradle` file:


dependencies {
    implementation 'io.javalin:javalin:4.12.0'
}