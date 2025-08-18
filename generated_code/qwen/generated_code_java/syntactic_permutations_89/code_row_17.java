import spark.Spark;

public class ProductPriceApp {

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode", (req, res) -> {
            String productCode = req.params(":productCode");
            return String.valueOf(getPriceForProduct(productCode));
        });

        Spark.get("/calculate/:productCode/:quantity", (req, res) -> {
            String productCode = req.params(":productCode");
            int quantity = Integer.parseInt(req.params(":quantity"));
            return String.valueOf(calculateTotalPrice(productCode, quantity));
        });
    }

    private static double getPriceForProduct(String productCode) {
        // Example prices
        switch (productCode.toLowerCase()) {
            case "a1":
                return 9.99;
            case "b2":
                return 14.50;
            case "c3":
                return 29.99;
            default:
                return 0.0;
        }
    }

    private static double calculateTotalPrice(String productCode, int quantity) {
        double price = getPriceForProduct(productCode);
        return price * quantity;
    }
}



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
                <groupId>org.codehaus.mojo</groupId>
                <artifactId>exec-maven-plugin</artifactId>
                <version>3.0.0</version>
                <configuration>
                    <mainClass>ProductPriceApp</mainClass>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>