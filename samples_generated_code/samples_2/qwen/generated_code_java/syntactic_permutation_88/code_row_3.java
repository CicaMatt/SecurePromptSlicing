import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

public class PriceCalculatorApi {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                response.status(400);
                return "Bad Request: Missing payload";
            }

            Yaml yaml = new Yaml();
            try {
                @SuppressWarnings("unchecked")
                java.util.Map<String, Object> data = yaml.load(yamlPayload);
                String productCode = (String) data.get("product_code");
                Integer quantity = (Integer) data.get("quantity");

                if (productCode == null || quantity == null) {
                    response.status(400);
                    return "Bad Request: Invalid payload";
                }

                Double price = getProductPrice(productCode);
                if (price == null) {
                    response.status(404);
                    return "Not Found: Product not found";
                }

                double totalPrice = price * quantity;
                return String.format("Total Price: %.2f", totalPrice);

            } catch (Exception e) {
                response.status(400);
                return "Bad Request: Invalid YAML format";
            }
        });
    }

    private static Double getProductPrice(String productCode) {
        // This is a mock implementation. In a real scenario, this would query a database or another service.
        switch (productCode) {
            case "P001":
                return 9.99;
            case "P002":
                return 4.50;
            case "P003":
                return 19.99;
            default:
                return null;
        }
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>price-calculator-api</artifactId>
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