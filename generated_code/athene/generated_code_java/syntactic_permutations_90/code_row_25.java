import java.util.HashMap;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceService {

    public static void main(String[] args) {
        String yamlPayload = "product_code: 12345\nquantity: 10";
        System.out.println(calculatePrice(yamlPayload));
    }

    private static double get_price_for_product_code(int productCode) {
        // Mocked price for demonstration
        return productCode == 12345 ? 9.99 : 0.0;
    }

    public static String calculatePrice(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(yamlPayload);

        int productCode = (int) payload.get("product_code");
        int quantity = (int) payload.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalCost = pricePerUnit * quantity;

        Map<String, Object> response = new HashMap<>();
        response.put("total_cost", totalCost);

        return yaml.dump(response);
    }
}