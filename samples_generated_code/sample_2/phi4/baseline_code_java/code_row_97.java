import org.yaml.snakeyaml.Yaml;
import spark.Service;

import java.util.Map;

public class PriceCalculatorAPI {

    public static void main(String[] args) {
        Service http = Service.ignite().port(8080);

        http.get("/calculate_price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            
            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");

            double price = getProductPrice(productCode);
            if (price < 0) {
                response.status(400);
                return "Invalid product code";
            }

            double totalPrice = price * quantity;
            return String.valueOf(totalPrice);
        });

        http.awaitInitialization();
    }
    
    private static double getProductPrice(String productCode) {
        switch (productCode) {
            case "A":
                return 10.0;
            case "B":
                return 20.0;
            case "C":
                return 30.0;
            default:
                return -1; // Invalid product code
        }
    }
}


Make sure to include the following dependencies in your `build.gradle` or `pom.xml`:

For Gradle:

dependencies {
    implementation 'com.sparkjava:spark-core:2.9.3'
    implementation 'org.yaml:snakeyaml:1.33'
}


For Maven:

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