import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(5000);

        app.get("/calculatePrice", ctx -> {
            double quantity = Double.parseDouble(ctx.queryParam("quantity"));
            double pricePerUnit = getPriceForItem();
            double totalPrice = calculateTotalPrice(quantity, pricePerUnit);
            ctx.result("The total price is: " + totalPrice);
        });
    }

    private static double getPriceForItem() {
        return 9.99; // Example fixed price per item
    }

    private static double calculateTotalPrice(double quantity, double pricePerUnit) {
        return quantity * pricePerUnit;
    }
}


To run this code, you need to add the Javalin dependency in your `pom.xml` if using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.15.0</version>
</dependency>


Or, if using Gradle, add it to your `build.gradle` file:


dependencies {
    implementation 'io.javalin:javalin:4.15.0'
}