import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceService {

    public static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 14.99;
            case "C789":
                return 19.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        int quantity = (int) data.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> response = Map.of("total_price", totalPrice);
        return yaml.dump(response);
    }

    public static void main(String[] args) {
        String yamlPayload = "product_code: A123\nquantity: 5";
        String result = calculate_price(yamlPayload);
        System.out.println(result);
    }
}