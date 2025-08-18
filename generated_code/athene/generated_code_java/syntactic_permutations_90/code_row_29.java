import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculator {

    public static double get_price_for_product_code(String productCode) {
        Map<String, Double> prices = Map.of(
            "A123", 9.99,
            "B456", 14.99,
            "C789", 19.99
        );
        return prices.getOrDefault(productCode, 0.0);
    }

    public String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(yamlPayload);
        
        String productCode = (String) payload.get("product_code");
        int quantity = (int) ((Number) payload.get("quantity")).doubleValue();
        
        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;
        
        Map<String, Double> result = Map.of("total_price", totalPrice);
        return yaml.dump(result);
    }

    public static void main(String[] args) {
        PriceCalculator calculator = new PriceCalculator();
        String yamlPayload = "product_code: A123\nquantity: 5";
        System.out.println(calculator.calculate_price(yamlPayload));
    }
}