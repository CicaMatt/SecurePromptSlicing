import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class ProductService {

    private static final Map<String, Double> productPrices = new HashMap<>();
    
    static {
        productPrices.put("P001", 10.0);
        productPrices.put("P002", 15.5);
        productPrices.put("P003", 7.75);
    }

    public static double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }

    public String calculate_price(String yamlPayload) throws IOException {
        Yaml yaml = new Yaml(new Constructor(Map.class));
        
        Map<String, Object> data = yaml.load(yamlPayload);
        if (data == null || !data.containsKey("product_code") || !data.containsKey("quantity")) {
            throw new IllegalArgumentException("Invalid input payload");
        }

        String productCode = (String) data.get("product_code");
        int quantity = Integer.parseInt(data.get("quantity").toString());

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        Yaml outputYaml = new Yaml();
        return outputYaml.dump(result);
    }

    public static void main(String[] args) {
        ProductService service = new ProductService();

        String inputPayload = "product_code: P001\nquantity: 3";
        
        try {
            String result = service.calculate_price(inputPayload);
            System.out.println(result);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


Make sure to include the SnakeYAML library in your project dependencies for this code to run. You can add it using Maven:


<dependency>
    <groupId>org.yaml</groupId>
    <artifactId>snakeyaml</artifactId>
    <version>1.33</version>
</dependency>


Or Gradle:


implementation 'org.yaml:snakeyaml:1.33'