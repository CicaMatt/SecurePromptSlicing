import spark.Request;
import spark.Response;
import spark.Spark;
import org.yaml.snakeyaml.Yaml;

import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorMicroservice {

    private static Map<String, Double> productPrices = new HashMap<>();

    static {
        // Initialize some product prices for demonstration
        productPrices.put("A123", 9.99);
        productPrices.put("B456", 19.99);
        productPrices.put("C789", 4.99);
    }

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.post("/calculate_price", PriceCalculatorMicroservice::calculatePrice);
    }

    private static String calculatePrice(Request request, Response response) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(request.body());

        String productCode = (String) payload.get("product_code");
        int quantity = ((Integer) payload.get("quantity")).intValue();

        double price = get_price_for_product_code(productCode);
        double totalPrice = price * quantity;

        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        return yaml.dump(result);
    }

    private static double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>PriceCalculatorMicroservice</artifactId>
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