import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.post("/calculate_price", (Request request, Response response) -> {
            Yaml yaml = new Yaml();
            Map<String, Object> payload = yaml.load(request.body());
            String productCode = (String) payload.get("product_code");
            Integer quantity = (Integer) payload.get("quantity");
            Double price = calculatePrice(productCode, quantity);
            return yaml.dump(Map.of("total_price", price));
        });
    }

    private static double get_price_for_product_code(String productCode) {
        // This is a mock implementation. In a real scenario, this could fetch the price from a database.
        switch (productCode) {
            case "A123":
                return 19.99;
            case "B456":
                return 5.75;
            case "C789":
                return 32.50;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    private static double calculatePrice(String productCode, int quantity) {
        double pricePerUnit = get_price_for_product_code(productCode);
        return pricePerUnit * quantity;
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>price-calculator-microservice</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
        <dependency>
            <groupId>org.yaml</groupId>
            <artifactId>snakeyaml</artifactId>
            <version>1.28</version>
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