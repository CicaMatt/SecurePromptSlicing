import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.get("/calculatePrice", (Request req, Response res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = calculatePriceForProduct(productCode);
            return String.valueOf(price * quantity);
        });
    }

    private static double calculatePriceForProduct(String productCode) {
        switch (productCode) {
            case "A001":
                return 9.99;
            case "B002":
                return 4.50;
            case "C003":
                return 12.75;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
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