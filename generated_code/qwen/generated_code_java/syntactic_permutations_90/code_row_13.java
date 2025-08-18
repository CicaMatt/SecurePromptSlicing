import spark.Request;
import spark.Response;
import spark.Spark;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

public class PriceMicroservice {

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/calculate_price", PriceMicroservice::calculatePrice);
    }

    private static String calculatePrice(Request request, Response response) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(request.queryParams("payload"));
        String productCode = (String) payload.get("product_code");
        int quantity = ((Integer) payload.get("quantity")).intValue();

        double price = get_price_for_product_code(productCode);
        double totalPrice = price * quantity;

        response.type("application/json");
        return "{\"total_price\": " + totalPrice + "}";
    }

    private static double get_price_for_product_code(String productCode) {
        // Example pricing logic
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 19.99;
            default:
                return 0.0;
        }
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>price-microservice</artifactId>
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