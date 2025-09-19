import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculatorAPI {

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);
        
        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");
        
        double pricePerUnit = getProductPrice(productCode);
        double totalPrice = pricePerUnit * quantity;
        
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
                return 0.0;
        }
    }

    public static void main(String[] args) {
        String yamlPayload = "product_code: A\nquantity: 5";
        System.out.println(calculate_price(yamlPayload));
    }
}