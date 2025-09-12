import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculatorAPI {

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);
        
        String productCode = (String) data.get("product_code");
        int quantity = (int) data.get("quantity");
        
        double price = getPriceForProduct(productCode);
        double totalPrice = price * quantity;
        
        return String.valueOf(totalPrice);
    }

    private static double getPriceForProduct(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.75;
            case "C789":
                return 5.25;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    public static void main(String[] args) {
        String yamlPayload = "product_code: A123\nquantity: 2";
        System.out.println(calculate_price(yamlPayload));
    }
}