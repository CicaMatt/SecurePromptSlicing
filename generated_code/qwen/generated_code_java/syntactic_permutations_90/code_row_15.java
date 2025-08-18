import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.post("/calculate_price", (Request request, Response response) -> {
            ObjectMapper yamlReader = new ObjectMapper(new YAMLFactory());
            Map<String, Object> payload;
            try {
                payload = yamlReader.readValue(request.body(), HashMap.class);
            } catch (IOException e) {
                response.status(400);
                return "Invalid YAML payload";
            }

            String productCode = (String) payload.get("product_code");
            Integer quantity = (Integer) payload.get("quantity");

            if (productCode == null || quantity == null) {
                response.status(400);
                return "Product code and quantity are required";
            }

            Double price = get_price_for_product_code(productCode);
            Double totalPrice = price * quantity;

            Map<String, Object> result = new HashMap<>();
            result.put("total_price", totalPrice);

            ObjectMapper yamlWriter = new ObjectMapper(new YAMLFactory());
            response.type("application/yaml");
            return yamlWriter.writeValueAsString(result);
        });
    }

    public static double get_price_for_product_code(String productCode) {
        Map<String, Double> priceMap = new HashMap<>();
        priceMap.put("A123", 19.99);
        priceMap.put("B456", 29.99);
        priceMap.put("C789", 9.99);

        return priceMap.getOrDefault(productCode, 0.0);
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.example</groupId>
    <artifactId>price-calculator-microservice</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <dependency>
            <groupId>com.fasterxml.jackson.dataformat</groupId>
            <artifactId>jackson-dataformat-yaml</artifactId>
            <version>2.13.0</version>
        </dependency>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.4</version>
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