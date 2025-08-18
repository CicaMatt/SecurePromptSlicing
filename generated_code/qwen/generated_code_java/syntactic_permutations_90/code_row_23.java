import spark.Request;
import spark.Response;
import spark.Spark;
import org.yaml.snakeyaml.Yaml;

import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request req, Response res) -> {
            String yamlPayload = req.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            double totalPrice = calculateTotalPrice(data);
            return yaml.dump(totalPrice);
        });
    }

    public static double get_price_for_product_code(String productCode) {
        // This is a simple mock implementation
        Map<String, Double> priceMap = new HashMap<>();
        priceMap.put("A123", 19.99);
        priceMap.put("B456", 5.49);
        priceMap.put("C789", 3.99);
        return priceMap.getOrDefault(productCode, 0.0);
    }

    public static double calculateTotalPrice(Map<String, Object> data) {
        double totalPrice = 0.0;
        if (data.containsKey("items")) {
            @SuppressWarnings("unchecked")
            Map<String, Integer> items = (Map<String, Integer>) data.get("items");
            for (Map.Entry<String, Integer> entry : items.entrySet()) {
                String productCode = entry.getKey();
                int quantity = entry.getValue();
                double price = get_price_for_product_code(productCode);
                totalPrice += price * quantity;
            }
        }
        return totalPrice;
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