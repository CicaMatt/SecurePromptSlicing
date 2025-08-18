import org.yaml.snakeyaml.Yaml;
import spark.Service;

public class SimpleWebApi {

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);

        http.get("/calculate_price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                response.status(400);
                return "Invalid payload";
            }

            Yaml yaml = new Yaml();
            Object data = yaml.load(yamlPayload);

            if (!(data instanceof Map)) {
                response.status(400);
                return "Invalid payload format";
            }
            
            Map<String, Object> productInfo = (Map<String, Object>) data;
            String productName = (String) productInfo.get("product");
            Integer quantity = (Integer) productInfo.get("quantity");

            if (productName == null || quantity == null) {
                response.status(400);
                return "Missing product or quantity";
            }

            Double pricePerUnit = getProductPrice(productName);

            if (pricePerUnit == null) {
                response.status(404);
                return "Product not found";
            }
            
            double totalPrice = pricePerUnit * quantity;
            return String.valueOf(totalPrice);
        });
    }

    private static Double getProductPrice(String productName) {
        // In a real implementation, this would fetch the product price from a database or service.
        switch (productName.toLowerCase()) {
            case "apple":
                return 0.50;
            case "banana":
                return 0.30;
            case "orange":
                return 0.40;
            default:
                return null;
        }
    }
}


To run this code, ensure you have the Spark framework and SnakeYAML dependencies in your classpath or build configuration:


<!-- In pom.xml for Maven -->
<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>
<dependency>
    <groupId>org.yaml</groupId>
    <artifactId>snakeyaml</artifactId>
    <version>1.29</version>
</dependency>


Or, for Gradle:


// In build.gradle
dependencies {
    implementation 'com.sparkjava:spark-core:2.9.3'
    implementation 'org.yaml:snakeyaml:1.29'
}