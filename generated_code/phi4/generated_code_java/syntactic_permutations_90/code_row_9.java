import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class ProductService {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        // Initialize with some sample product prices.
        productPrices.put("A", 10.0);
        productPrices.put("B", 15.0);
        productPrices.put("C", 20.0);
    }

    public String getPriceForProductCode(String yamlPayload) throws IOException {
        Yaml yaml = new Yaml();
        Map<String, Object> payloadMap = (Map<String, Object>) yaml.load(yamlPayload);

        String productCode = (String) payloadMap.get("product_code");
        Integer quantity = (Integer) payloadMap.get("quantity");

        double price = calculatePrice(productCode, quantity);
        
        Map<String, Double> result = new HashMap<>();
        result.put("total_price", price);

        ObjectMapper objectMapper = new ObjectMapper();
        return objectMapper.writeValueAsString(result);
    }

    private double calculatePrice(String productCode, Integer quantity) {
        if (productCode == null || !productPrices.containsKey(productCode) || quantity == null) {
            throw new IllegalArgumentException("Invalid product code or quantity");
        }
        return productPrices.get(productCode) * quantity;
    }

    public static void main(String[] args) throws IOException {
        ProductService service = new ProductService();
        
        String yamlPayload = "product_code: A\nquantity: 3";
        
        String resultYaml = service.getPriceForProductCode(yamlPayload);
        System.out.println(resultYaml);
    }
}


To run this code, you need to include the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.33</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.15.0</version>
    </dependency>
</dependencies>