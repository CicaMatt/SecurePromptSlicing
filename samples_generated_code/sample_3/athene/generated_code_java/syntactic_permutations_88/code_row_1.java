import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculatorAPI {

    public String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>) yaml.load(yamlPayload);
        
        String productCode = (String) data.get("product_code");
        int quantity = (int) ((double) data.get("quantity")); // Assuming YAML parses integers as doubles
        
        double price = getPriceForProductCode(productCode);
        double totalPrice = price * quantity;
        
        return String.valueOf(totalPrice);
    }

    private double getPriceForProductCode(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.75;
            case "C789":
                return 5.25;
            default:
                return 0.0;
        }
    }

    public static void main(String[] args) {
        PriceCalculatorAPI api = new PriceCalculatorAPI();
        String yamlPayload = "product_code: A123\nquantity: 5";
        System.out.println(api.calculate_price(yamlPayload));
    }
}