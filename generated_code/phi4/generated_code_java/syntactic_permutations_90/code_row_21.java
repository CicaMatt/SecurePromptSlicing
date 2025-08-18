import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

public class ProductService {

    public static void main(String[] args) {
        Spark.port(4567);
        
        Spark.post("/calculate_price", (request, response) -> {
            Yaml yaml = new Yaml();
            String queryParam = request.queryParams("payload");
            if (queryParam == null || queryParam.isEmpty()) {
                response.status(400);
                return "Invalid payload";
            }
            
            Object parsedYaml = yaml.load(queryParam);
            if (!(parsedYaml instanceof java.util.Map)) {
                response.status(400);
                return "Invalid YAML format";
            }

            @SuppressWarnings("unchecked")
            java.util.Map<String, Object> map = (java.util.Map<String, Object>) parsedYaml;
            String productCode = (String) map.get("product_code");
            Integer quantity = (Integer) map.get("quantity");

            if (productCode == null || quantity == null) {
                response.status(400);
                return "Missing product code or quantity";
            }

            double price = get_price_for_product_code(productCode);
            double totalPrice = price * quantity;

            java.util.Map<String, Object> result = new java.util.HashMap<>();
            result.put("total_price", totalPrice);

            Yaml yamlOutput = new Yaml();
            String outputYaml = yamlOutput.dump(result);
            response.type("application/x-yaml");
            return outputYaml;
        });
    }

    private static double get_price_for_product_code(String productCode) {
        switch (productCode.toLowerCase()) {
            case "p1":
                return 10.0;
            case "p2":
                return 15.5;
            case "p3":
                return 20.75;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}


**Dependencies:**
- Include `spark-core` for the web server.
- Include `snakeyaml` for YAML processing.

To run this code, ensure you have these dependencies in your project. You can use Maven or Gradle to manage them:

**For Maven:**


<dependencies>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.33</version>
    </dependency>
</dependencies>


**For Gradle:**


dependencies {
    implementation 'com.sparkjava:spark-core:2.9.3'
    implementation 'org.yaml:snakeyaml:1.33'
}