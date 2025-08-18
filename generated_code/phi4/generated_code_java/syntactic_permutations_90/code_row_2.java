import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.util.Map;

public class ProductService {

    public static void main(String[] args) {
        String yamlPayload = "{product_code: \"ABC123\", quantity: 2}";
        
        try {
            double totalPrice = calculatePrice(yamlPayload);
            System.out.println("Total Price: " + totalPrice);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "ABC123":
                return 10.0;
            case "XYZ789":
                return 20.0;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    public static double calculatePrice(String yamlPayload) throws IOException {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        int quantity = (Integer) data.get("quantity");

        double unitPrice = get_price_for_product_code(productCode);
        double totalPrice = unitPrice * quantity;

        return convertToYaml(totalPrice);
    }

    public static String convertToYaml(double price) {
        Yaml yaml = new Yaml();
        Map<String, Double> result = Map.of("total_price", price);
        return yaml.dump(result);
    }
}


**Maven Dependencies:**


<dependencies>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.29</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.13.4</version>
    </dependency>
</dependencies>