import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculator {

    public static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.75;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(yamlPayload);

        String productCode = (String) payload.get("product_code");
        int quantity = (int) ((Double) payload.get("quantity")).doubleValue();

        double unitPrice = get_price_for_product_code(productCode);
        double totalPrice = unitPrice * quantity;

        Map<String, Double> result = Map.of("total_price", totalPrice);

        return yaml.dump(result);
    }

    public static void main(String[] args) {
        String yamlPayload = "product_code: A123\nquantity: 5";
        System.out.println(calculate_price(yamlPayload));
    }
}