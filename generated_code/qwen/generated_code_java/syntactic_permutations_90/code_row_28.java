import spark.Request;
import spark.Spark;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

public class PriceCalculatorService {

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            
            String productCode = (String) data.get("product_code");
            int quantity = (Integer) data.get("quantity");

            double totalPrice = calculatePrice(productCode, quantity);
            response.type("application/json");
            return "{\"total_price\": " + totalPrice + "}";
        });
    }

    public static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A001":
                return 9.99;
            case "B002":
                return 14.99;
            case "C003":
                return 19.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }

    public static double calculatePrice(String productCode, int quantity) {
        double pricePerUnit = get_price_for_product_code(productCode);
        return pricePerUnit * quantity;
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>price-calculator-service</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.4</version>
        </dependency>
        <dependency>
            <groupId>org.yaml</groupId>
            <artifactId>snakeyaml</artifactId>
            <version>1.30</version>
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