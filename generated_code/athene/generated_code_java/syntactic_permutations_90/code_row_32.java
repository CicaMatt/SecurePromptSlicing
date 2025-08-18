import java.util.HashMap;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculator {

    public static void main(String[] args) {
        String yamlPayload = "product_code: A123\nquantity: 5";
        System.out.println(calculatePrice(yamlPayload));
    }

    private static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.99;
            case "B456":
                return 5.99;
            case "C789":
                return 15.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }

    public static String calculatePrice(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(yamlPayload);
        String productCode = (String) payload.get("product_code");
        Integer quantity = (Integer) payload.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        return yaml.dump(result);
    }
}