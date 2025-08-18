import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

public class ProductService {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        // Example products and their prices
        productPrices.put("A123", 10.0);
        productPrices.put("B456", 20.0);
        productPrices.put("C789", 30.0);
    }

    public static double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }

    public static String calculate_price(String yamlPayload) throws IOException {
        Yaml yaml = new Yaml(new Constructor(Map.class));
        Map<String, Object> dataMap = yaml.load(yamlPayload);

        if (dataMap == null || !dataMap.containsKey("product_code") || !dataMap.containsKey("quantity")) {
            return "Invalid payload";
        }

        String productCode = (String) dataMap.get("product_code");
        int quantity = ((Number) dataMap.get("quantity")).intValue();

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        Yaml resultYaml = new Yaml();
        return resultYaml.dump(result);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Enter YAML payload:");
        String yamlPayload = reader.readLine();

        String result = calculate_price(yamlPayload);
        System.out.println(result);
    }
}


To run this code, you will need to add the SnakeYAML library dependency. If using Maven, include:


<dependency>
    <groupId>org.yaml</groupId>
    <artifactId>snakeyaml</artifactId>
    <version>1.33</version>
</dependency>