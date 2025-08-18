import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

import java.io.StringReader;
import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorApi {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A123", 19.99);
        productPrices.put("B456", 29.99);
        productPrices.put("C789", 39.99);
    }

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request req, spark.Response res) -> {
            String yamlPayload = req.queryParams("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                return "Invalid request: payload is required";
            }
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(new StringReader(yamlPayload));
            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");

            if (productCode == null || quantity == null) {
                return "Invalid request: product_code and quantity are required";
            }

            Double price = productPrices.get(productCode);
            if (price == null) {
                return "Product not found";
            }

            double totalPrice = price * quantity;
            return String.format("Total Price: %.2f", totalPrice);
        });
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.example</groupId>
    <artifactId>PriceCalculatorApi</artifactId>
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