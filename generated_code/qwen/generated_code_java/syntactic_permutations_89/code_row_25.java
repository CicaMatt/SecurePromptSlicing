import spark.Request;
import spark.Response;
import spark.Spark;

public class App {
    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode/:quantity", (Request request, Response response) -> {
            String productCode = request.params("productCode");
            int quantity = Integer.parseInt(request.params("quantity"));
            double price = getProductPrice(productCode) * quantity;
            return String.format("%.2f", price);
        });
    }

    public static double getProductPrice(String productCode) {
        // This is a simple mock-up of a method to get the price based on product code
        switch (productCode) {
            case "A1":
                return 9.99;
            case "B2":
                return 19.95;
            case "C3":
                return 4.75;
            default:
                return 0.0;
        }
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>webapp</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
    </dependencies>
</project>