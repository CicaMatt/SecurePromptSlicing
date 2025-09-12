import spark.Spark;
import org.yaml.snakeyaml.Yaml;
import java.util.Map;

public class PriceService {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");
            Double price = get_price_for_product_code(productCode);
            double totalPrice = price * quantity;
            return yaml.dump(Map.of("total_price", totalPrice));
        });
    }

    public static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A001":
                return 19.99;
            case "B002":
                return 5.49;
            case "C003":
                return 3.89;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>price-service</artifactId>
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
            <version>1.27</version>
        </dependency>
    </dependencies>
</project>