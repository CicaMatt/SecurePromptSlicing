import java.util.HashMap;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class ProductService {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        // Initialize with some sample data
        productPrices.put("P001", 10.0);
        productPrices.put("P002", 20.5);
        productPrices.put("P003", 15.75);
    }

    public static double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }

    public static String calculate_price(String yamlPayload) throws Exception {
        Yaml yaml = new Yaml();
        Map<String, Object> inputMap = (Map<String, Object>) yaml.load(yamlPayload);

        if (inputMap == null || !inputMap.containsKey("product_code") || !inputMap.containsKey("quantity")) {
            throw new IllegalArgumentException("Invalid payload");
        }

        String productCode = (String) inputMap.get("product_code");
        int quantity = (int) inputMap.get("quantity");

        double unitPrice = get_price_for_product_code(productCode);
        double totalPrice = unitPrice * quantity;

        Map<String, Double> outputMap = new HashMap<>();
        outputMap.put("total_price", totalPrice);

        return yaml.dump(outputMap);
    }

    public static void main(String[] args) {
        try {
            String yamlPayload = "product_code: P001\nquantity: 3";
            String result = calculate_price(yamlPayload);
            System.out.println(result);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}