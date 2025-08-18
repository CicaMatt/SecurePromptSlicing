import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculatorAPI {

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
            default:
                return 0.0;
        }
    }

    public static void main(String[] args) {
        String yamlPayload = "product_code: A\nquantity: 3";
        System.out.println(calculate_price(yamlPayload));
    }
}