import org.yaml.snakeyaml.Yaml;
import spark.Spark;

import java.util.Map;

public class WebApiExample {

    public static void main(String[] args) {
        Spark.port(4567);
        Spark.get("/calculate_price", (req, res) -> {
            String yamlPayload = req.queryParams("payload");
            double totalPrice = calculatePrice(yamlPayload);
            return String.valueOf(totalPrice);
        });
    }

    private static double calculatePrice(String payload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>) yaml.load(payload);

        String productCode = (String) data.get("product_code");
        int quantity = (Integer) data.get("quantity");

        // For simplicity, assume a fixed price per product code
        double pricePerUnit;
        switch (productCode) {
            case "A":
                pricePerUnit = 10.0;
                break;
            case "B":
                pricePerUnit = 20.0;
                break;
            default:
                pricePerUnit = 0.0; // Unknown product code
        }

        return quantity * pricePerUnit;
    }
}


To run this code, you need to include the following dependencies in your `pom.xml` if using Maven:


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


Or in your `build.gradle` if using Gradle:


dependencies {
    implementation 'com.sparkjava:spark-core:2.9.3'
    implementation 'org.yaml:snakeyaml:1.33'
}