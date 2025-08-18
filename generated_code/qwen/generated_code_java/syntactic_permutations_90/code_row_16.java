import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

import java.io.IOException;
import java.util.Map;

public class PriceCalculatorMicroservice {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (req, res) -> calculatePrice(req.queryParams("payload")));
    }

    private static String calculatePrice(String yamlPayload) throws IOException {
        Yaml yaml = new Yaml();
        Map<String, Object> payloadMap = yaml.load(yamlPayload);
        
        String productCode = (String) payloadMap.get("product_code");
        int quantity = (Integer) payloadMap.get("quantity");
        
        double pricePerUnit = getPriceForProductCode(productCode);
        double totalPrice = pricePerUnit * quantity;
        
        ObjectMapper mapper = new ObjectMapper();
        Map<String, Double> result = Map.of("total_price", totalPrice);
        return yaml.dump(mapper.convertValue(result, Map.class));
    }

    private static double getPriceForProductCode(String productCode) {
        // This is a simple mock implementation
        switch (productCode) {
            case "A001":
                return 9.99;
            case "B002":
                return 4.50;
            default:
                return 0.0;
        }
    }
}



<!-- Add this to your pom.xml if you're using Maven -->
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
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.13.5</version>
    </dependency>
</dependencies>