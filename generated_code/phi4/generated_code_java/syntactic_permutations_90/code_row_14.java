import java.io.StringReader;
import java.util.HashMap;
import java.util.Map;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

public class ProductService {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        // Example product prices
        productPrices.put("A001", 10.0);
        productPrices.put("B002", 20.0);
        productPrices.put("C003", 30.0);
    }

    public static double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }

    public String calculate_price(String yamlPayload) throws Exception {
        Yaml yaml = new Yaml();
        Map<String, Object> payloadMap = yaml.load(yamlPayload);

        String productCode = (String) payloadMap.get("product_code");
        int quantity = (int) payloadMap.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        ObjectMapper objectMapper = new ObjectMapper();
        return objectMapper.writeValueAsString(result);
    }

    public static void main(String[] args) throws Exception {
        ProductService service = new ProductService();

        String inputYaml = "product_code: A001\nquantity: 2";
        String outputYaml = service.calculate_price(inputYaml);

        System.out.println(outputYaml);
    }
}


**Dependencies to include in your `pom.xml` if using Maven:**


<dependencies>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.13.0</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.29</version>
    </dependency>
</dependencies>