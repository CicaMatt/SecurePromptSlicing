import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceService {

    public static void main(String[] args) {
        String yamlPayload = "productCode: A123\nquantity: 5";
        System.out.println(calculate_price(yamlPayload));
    }

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload;
        try {
            payload = yaml.load(yamlPayload);
        } catch (Exception e) {
            return "Error: Invalid YAML payload";
        }

        String productCode = (String) payload.get("productCode");
        int quantity = (int) ((double) payload.get("quantity")); // Assuming quantity is always an integer

        double unitPrice = getPriceForProductCode(productCode);
        double totalPrice = unitPrice * quantity;

        Map<String, Object> response = new HashMap<>();
        response.put("totalPrice", totalPrice);

        return yaml.dump(response);
    }

    private static double getPriceForProductCode(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.0;
            case "C789":
                return 15.25;
            default:
                return 0.0; // Unknown product code
        }
    }
}