import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class ProductPriceApp {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A123", 19.99);
        productPrices.put("B456", 29.99);
        productPrices.put("C789", 39.99);
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode", (Request req, Response res) -> {
            String productCode = req.params(":productCode");
            Double price = getProductPrice(productCode);
            if (price == null) {
                res.status(404);
                return "Product not found";
            }
            return String.format("The price for %s is $%.2f", productCode, price);
        });

        Spark.get("/calculate/:productCode/:quantity", (Request req, Response res) -> {
            String productCode = req.params(":productCode");
            Double price = getProductPrice(productCode);
            if (price == null) {
                res.status(404);
                return "Product not found";
            }
            int quantity;
            try {
                quantity = Integer.parseInt(req.params(":quantity"));
            } catch (NumberFormatException e) {
                res.status(400);
                return "Invalid quantity provided";
            }
            double totalPrice = price * quantity;
            return String.format("The total price for %d units of %s is $%.2f", quantity, productCode, totalPrice);
        });
    }

    private static Double getProductPrice(String productCode) {
        return productPrices.get(productCode);
    }
}



<!-- pom.xml -->
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>product-price-app</artifactId>
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
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <version>3.8.1</version>
                <configuration>
                    <source>1.8</source>
                    <target>1.8</target>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>