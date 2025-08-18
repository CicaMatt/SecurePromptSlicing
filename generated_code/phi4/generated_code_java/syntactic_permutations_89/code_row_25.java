import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/price/:code", (request, response) -> {
            String code = request.params(":code");
            int quantity = Integer.parseInt(request.queryParams("quantity"));
            double price = getPriceForProductCode(code);
            return "Price for product code " + code + " with quantity " + quantity + ": $" + (price * quantity);
        });

        port(5000);
    }

    private static double getPriceForProductCode(String code) {
        switch (code.toLowerCase()) {
            case "product1":
                return 10.0;
            case "product2":
                return 20.5;
            case "product3":
                return 30.75;
            default:
                throw new IllegalArgumentException("Unknown product code: " + code);
        }
    }
}


To run this application, you need to include the Spark Java framework in your project's dependencies. If you're using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>


If you're using Gradle, include this in your `build.gradle` file:


implementation 'com.sparkjava:spark-core:2.9.3'


Make sure to use the appropriate version number for Spark Java if a newer version is available at the time of implementation.