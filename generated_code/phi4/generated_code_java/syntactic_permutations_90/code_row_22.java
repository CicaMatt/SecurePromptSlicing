import java.io.StringReader;
import org.yaml.snakeyaml.Yaml;

public class ProductService {

    public static void main(String[] args) {
        // Example usage
        String yamlPayload = "products:\n  - code: A123\n    quantity: 2\n  - code: B456\n    quantity: 1";
        String resultYaml = calculatePrice(yamlPayload);
        System.out.println(resultYaml);
    }

    public static double getPriceForProductCode(String productCode) {
        // Simulated product price database
        switch (productCode) {
            case "A123":
                return 10.0;
            case "B456":
                return 20.0;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    public static String calculatePrice(String yamlPayload) {
        Yaml yaml = new Yaml();
        java.util.Map<String, Object> payloadMap = yaml.load(new StringReader(yamlPayload));
        
        if (payloadMap == null || !payloadMap.containsKey("products")) {
            throw new IllegalArgumentException("Invalid YAML payload");
        }

        java.util.List<?> products = (java.util.List<?>) payloadMap.get("products");
        double totalPrice = 0.0;

        for (Object productObj : products) {
            java.util.Map<String, Object> product = (java.util.Map<String, Object>) productObj;
            String code = (String) product.get("code");
            int quantity = ((Number) product.get("quantity")).intValue();

            double price = getPriceForProductCode(code);
            totalPrice += price * quantity;
        }

        java.util.LinkedHashMap<String, Double> resultMap = new java.util.LinkedHashMap<>();
        resultMap.put("total_price", totalPrice);

        return yaml.dump(resultMap);
    }
}
