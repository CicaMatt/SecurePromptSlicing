import spark.Request;
import spark.Spark;
import org.yaml.snakeyaml.Yaml;
import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);

            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");

            Double pricePerUnit = getPriceForProductCode(productCode);
            Double totalPrice = calculatePrice(pricePerUnit, quantity);

            Map<String, Object> result = Map.of("total_price", totalPrice);
            return yaml.dump(result);
        });
    }

    public static Double getPriceForProductCode(String productCode) {
        // This is a simple mock implementation
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 19.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }

    public static Double calculatePrice(Double pricePerUnit, Integer quantity) {
        return pricePerUnit * quantity;
    }
}



<!-- pom.xml for Maven to include the necessary dependencies -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
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
</project>