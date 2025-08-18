import java.io.IOException;
import java.util.HashMap;
import org.yaml.snakeyaml.Yaml;

public class ProductService {

    public static double get_price_for_product_code(String productCode) {
        switch (productCode.toLowerCase()) {
            case "apple":
                return 1.0;
            case "banana":
                return 0.5;
            case "orange":
                return 0.8;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    public static String calculate_price(String yamlPayload) throws IOException {
        Yaml yaml = new Yaml();
        HashMap<String, Object> map = (HashMap<String, Object>) yaml.load(yamlPayload);

        String productCode = (String) map.get("product_code");
        int quantity = (int) map.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        HashMap<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        return yaml.dump(result);
    }

    public static void main(String[] args) {
        try {
            String queryParamYaml = "product_code: apple\nquantity: 3";
            String resultYaml = calculate_price(queryParamYaml);
            System.out.println(resultYaml);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


To run this code, you need to include the SnakeYAML library in your project. If you're using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>org.yaml</groupId>
    <artifactId>snakeyaml</artifactId>
    <version>1.33</version>
</dependency>