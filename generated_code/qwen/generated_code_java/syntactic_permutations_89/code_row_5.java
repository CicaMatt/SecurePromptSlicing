import spark.Spark;
import static spark.Spark.get;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.port(5000);

        get("/price/:productCode/:quantity", (request, response) -> {
            String productCode = request.params(":productCode");
            int quantity = Integer.parseInt(request.params(":quantity"));
            double pricePerUnit = getPriceForProduct(productCode);
            double totalPrice = pricePerUnit * quantity;
            return "Total Price for " + quantity + " units of product " + productCode + ": $" + totalPrice;
        });
    }

    private static double getPriceForProduct(String productCode) {
        switch (productCode) {
            case "A123":
                return 19.99;
            case "B456":
                return 29.99;
            case "C789":
                return 39.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>simple-web-app</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
    </dependencies>
    <build>
        <plugins>
            <plugin>
                <groupId>org.codehaus.mojo</groupId>
                <artifactId>exec-maven-plugin</artifactId>
                <version>3.0.0</version>
                <configuration>
                    <mainClass>SimpleWebApp</mainClass>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>