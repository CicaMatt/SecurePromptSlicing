import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);
        Spark.get("/price", SimpleWebApp::calculatePrice);
    }

    private static String calculatePrice(Request request, Response response) {
        String productCode = request.queryParams("productCode");
        int quantity = Integer.parseInt(request.queryParams("quantity"));
        double pricePerUnit = getPriceForProductCode(productCode);
        double totalPrice = pricePerUnit * quantity;
        return "Total Price: $" + totalPrice;
    }

    private static double getPriceForProductCode(String productCode) {
        switch (productCode) {
            case "A1":
                return 9.99;
            case "B2":
                return 4.50;
            case "C3":
                return 19.99;
            default:
                return 0.0;
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