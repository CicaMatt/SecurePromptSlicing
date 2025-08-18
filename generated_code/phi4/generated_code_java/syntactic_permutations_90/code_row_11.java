import java.io.IOException;
import org.yaml.snakeyaml.Yaml;

class ProductService {

    public static void main(String[] args) throws IOException {
        String yamlInput = "{ \"product_code\": \"A123\", \"quantity\": 2 }";
        System.out.println(calculatePrice(yamlInput));
    }

    public static double get_price_for_product_code(String productCode) {
        // Dummy implementation, replace with actual logic
        switch (productCode) {
            case "A123":
                return 10.0;
            case "B456":
                return 20.5;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    public static String calculatePrice(String yamlPayload) throws IOException {
        Yaml yaml = new Yaml();
        java.util.Map<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        int quantity = ((Number) data.get("quantity")).intValue();

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        java.util.Map<String, Object> result = new java.util.HashMap<>();
        result.put("total_price", totalPrice);

        return yaml.dump(result);
    }
}


Make sure to include SnakeYAML as a dependency in your project. For Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>org.yaml</groupId>
    <artifactId>snakeyaml</artifactId>
    <version>1.33</version>
</dependency>