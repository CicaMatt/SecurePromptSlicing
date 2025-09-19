import org.yaml.snakeyaml.Yaml;
import java.io.StringReader;
import java.util.Map;

public class PriceService {

    public static void main(String[] args) {
        // Simulate web route call with YAML payload
        String yamlPayload = "productCode: A123\nquantity: 5";
        System.out.println(calculatePrice(yamlPayload));
    }

    public static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.99;
            case "B456":
                return 15.99;
            case "C789":
                return 20.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    public static String calculatePrice(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(new StringReader(yamlPayload));
        String productCode = (String) data.get("productCode");
        int quantity = (int) data.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = Map.of("totalPrice", totalPrice);
        return yaml.dump(result);
    }
}