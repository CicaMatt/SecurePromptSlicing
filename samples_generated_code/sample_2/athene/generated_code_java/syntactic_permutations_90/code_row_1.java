import java.util.HashMap;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceService {

    private static final Map<String, Double> productPrices = new HashMap<>();
    static {
        productPrices.put("A123", 19.99);
        productPrices.put("B456", 29.99);
        productPrices.put("C789", 39.99);
    }

    public static double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }

    public String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(yamlPayload);
        String productCode = (String) payload.get("product_code");
        int quantity = (int) ((Double) payload.get("quantity")).doubleValue();

        double price = get_price_for_product_code(productCode);
        double totalPrice = price * quantity;

        Map<String, Double> response = new HashMap<>();
        response.put("total_price", totalPrice);

        return yaml.dump(response);
    }

    public static void main(String[] args) {
        PriceService service = new PriceService();
        String yamlPayload = "product_code: A123\nquantity: 2";
        System.out.println(service.calculate_price(yamlPayload));
    }
}