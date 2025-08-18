import spark.Request;
import spark.Response;
import spark.Spark;

public class ProductPriceCalculator {

    public static void main(String[] args) {
        Spark.get("/calculate-price", (Request req, Response res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = calculatePrice(productCode);
            return "Total Price for " + quantity + " units of product " + productCode + ": $" + (price * quantity);
        });
    }

    public static double calculatePrice(String productCode) {
        switch (productCode) {
            case "A101":
                return 9.99;
            case "B202":
                return 14.50;
            case "C303":
                return 29.75;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>product-price-calculator</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
    </dependencies>
</project>