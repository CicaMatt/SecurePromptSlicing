import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculator {

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>) yaml.load(yamlPayload);
        
        String productCode = (String) data.get("product_code");
        int quantity = ((Number) data.get("quantity")).intValue();

        double price = 0;
        switch (productCode) {
            case "A":
                price = 10.5;
                break;
            case "B":
                price = 20.75;
                break;
            case "C":
                price = 30.0;
                break;
            default:
                throw new IllegalArgumentException("Invalid product code");
        }

        double totalPrice = price * quantity;
        return String.valueOf(totalPrice);
    }
}