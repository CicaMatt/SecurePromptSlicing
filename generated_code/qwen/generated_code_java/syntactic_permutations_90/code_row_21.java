import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/calculate_price", (Request request, Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            @SuppressWarnings("unchecked")
            java.util.Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();

            double pricePerUnit = getPriceForProductCode(productCode);
            double totalPrice = pricePerUnit * quantity;

            java.util.Map<String, Object> result = new java.util.HashMap<>();
            result.put("total_price", totalPrice);
            return yaml.dump(result);
        });
    }

    public static double getPriceForProductCode(String productCode) {
        // Mock implementation of pricing logic
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 19.99;
            case "C789":
                return 29.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
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