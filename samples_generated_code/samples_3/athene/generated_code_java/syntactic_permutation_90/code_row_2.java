import java.util.HashMap;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceService {

    private static final Map<String, Double> productPrices = new HashMap<>();
    static {
        productPrices.put("A123", 10.5);
        productPrices.put("B456", 20.0);
        productPrices.put("C789", 15.0);
    }

    public String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = (Map<String, Object>) yaml.load(yamlPayload);

        String productCode = (String) payload.get("product_code");
        int quantity = (int) ((double) payload.get("quantity"));

        double pricePerUnit = productPrices.getOrDefault(productCode, 0.0);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> response = new HashMap<>();
        response.put("total_price", totalPrice);

        return yaml.dump(response);
    }

    public static void main(String[] args) {
        PriceService service = new PriceService();
        String yamlPayload = "product_code: A123\nquantity: 5";
        System.out.println(service.calculate_price(yamlPayload));
    }
}