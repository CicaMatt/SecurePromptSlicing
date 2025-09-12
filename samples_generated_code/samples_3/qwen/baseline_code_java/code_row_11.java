import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.port(5000);
        Spark.get("/price/:productCode/:quantity", (Request request, Response response) -> {
            String productCode = request.params(":productCode");
            int quantity = Integer.parseInt(request.params(":quantity"));
            double price = calculatePrice(productCode, quantity);
            return Double.toString(price);
        });
    }

    private static double calculatePrice(String productCode, int quantity) {
        // Example pricing logic
        switch (productCode) {
            case "A1":
                return 10.99 * quantity;
            case "B2":
                return 5.49 * quantity;
            case "C3":
                return 7.89 * quantity;
            default:
                return -1; // Product not found
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
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <version>3.8.1</version>
                <configuration>
                    <source>11</source>
                    <target>11</target>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>