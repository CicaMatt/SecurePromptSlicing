import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.util.Map;

public class PriceCalculator {
    public static void main(String[] args) throws IOException {
        String yamlPayload = "{product_code: '12345', quantity: 2}"; // Example payload
        System.out.println(calculatePrice(yamlPayload));
    }

    public static String calculatePrice(String yamlPayload) throws IOException {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);
        
        String productCode = (String) data.get("product_code");
        int quantity = ((Number) data.get("quantity")).intValue();

        double price = getProductPrice(productCode);
        return "Total Price: $" + (price * quantity);
    }

    private static double getProductPrice(String productCode) {
        // Example pricing logic
        Map<String, Double> productPrices = Map.of(
            "12345", 10.0,
            "67890", 15.5
        );

        return productPrices.getOrDefault(productCode, 0.0);
    }
}


**Dependencies:**

To run this code, include the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.30</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.13.3</version>
    </dependency>
</dependencies>