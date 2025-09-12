import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

import java.io.ByteArrayInputStream;
import java.nio.charset.StandardCharsets;
import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.get("/calculate_price", (Request req, spark.Response res) -> {
            String yamlPayload = req.queryParams("payload");
            Yaml yaml = new Yaml();
            ObjectMapper objectMapper = new ObjectMapper();

            Map<String, Object> data = yaml.load(new ByteArrayInputStream(yamlPayload.getBytes(StandardCharsets.UTF_8)));
            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();

            double totalPrice = calculatePrice(productCode, quantity);

            Map<String, Double> responseMap = Map.of("total_price", totalPrice);
            return yaml.dump(objectMapper.convertValue(responseMap, Map.class));
        });
    }

    private static double get_price_for_product_code(String productCode) {
        // Mock implementation for demonstration purposes
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 15.50;
            default:
                return 0.0;
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
        <dependency>
            <groupId>com.fasterxml.jackson.core</groupId>
            <artifactId>jackson-databind</artifactId>
            <version>2.13.0</version>
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