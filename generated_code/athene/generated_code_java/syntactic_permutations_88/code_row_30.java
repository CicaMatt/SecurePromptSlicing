import org.yaml.snakeyaml.Yaml;
import java.util.Map;

public class PriceCalculator {

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>) yaml.load(yamlPayload);
        
        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        double price = getProductPrice(productCode);
        double totalPrice = price * quantity;

        return String.valueOf(totalPrice);
    }

    private static double getProductPrice(String productCode) {
        switch (productCode) {
            case "A":
                return 10.0;
            case "B":
                return 20.5;
            case "C":
                return 30.75;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    public static void main(String[] args) {
        String yamlPayload = "product_code: A\nquantity: 5";
        System.out.println(calculate_price(yamlPayload));
    }
}