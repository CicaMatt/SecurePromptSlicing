import org.yaml.snakeyaml.Yaml;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class ProductService {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("P001", 10.0);
        productPrices.put("P002", 20.0);
        productPrices.put("P003", 30.0);
    }

    public static void main(String[] args) {
        Spark.port(4567);

        Spark.post("/get_price_for_product_code", (req, res) -> {
            Yaml yaml = new Yaml();
            Map<String, Object> payloadMap = yaml.load(req.queryParams("payload"));
            
            String productCode = (String) payloadMap.get("product_code");
            Integer quantity = (Integer) payloadMap.get("quantity");

            double totalPrice = calculateTotalPrice(productCode, quantity);
            Map<String, Double> responseMap = new HashMap<>();
            responseMap.put("total_price", totalPrice);

            res.type("application/x-yaml");
            return yaml.dump(responseMap);
        });

    }

    private static double calculateTotalPrice(String productCode, Integer quantity) {
        if (productPrices.containsKey(productCode)) {
            return productPrices.get(productCode) * quantity;
        }
        return 0.0;
    }
}


Ensure you have the following dependencies in your `pom.xml` for Maven or equivalent setup if using a different build tool:


<dependencies>
    <!-- Spark Java dependency -->
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>

    <!-- SnakeYAML dependency -->
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.33</version>
    </dependency>
</dependencies>