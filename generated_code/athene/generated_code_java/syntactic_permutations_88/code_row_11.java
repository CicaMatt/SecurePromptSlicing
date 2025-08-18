import org.yaml.snakeyaml.Yaml;
import java.io.StringReader;
import java.util.Map;

public class PriceCalculatorAPI {

    public String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(new StringReader(yamlPayload));
        
        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");
        
        double price = getPriceForProduct(productCode);
        double totalPrice = price * quantity;
        
        return String.valueOf(totalPrice);
    }

    private double getPriceForProduct(String productCode) {
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
        PriceCalculatorAPI api = new PriceCalculatorAPI();
        String yamlPayload = "product_code: A123\nquantity: 5";
        System.out.println(api.calculate_price(yamlPayload));
    }
}