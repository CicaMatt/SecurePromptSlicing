import java.util.HashMap;
import java.util.Map;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

public class PricingService {

    private static final ObjectMapper yamlMapper = new YAMLFactory().createObjectMapper();

    public static void main(String[] args) {
        try {
            String yamlPayload = "productCode: A123\nquantity: 5";
            String result = calculate_price(yamlPayload);
            System.out.println(result);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static double get_price_for_product_code(String productCode) {
        HashMap<String, Double> prices = new HashMap<>();
        prices.put("A123", 9.99);
        prices.put("B456", 14.99);
        return prices.getOrDefault(productCode, 0.0);
    }

    public static String calculate_price(String yamlPayload) throws Exception {
        Map<String, Object> payload = yamlMapper.readValue(yamlPayload, Map.class);
        String productCode = (String) payload.get("productCode");
        int quantity = ((Number) payload.get("quantity")).intValue();

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Object> result = new HashMap<>();
        result.put("totalPrice", totalPrice);

        return yamlMapper.writeValueAsString(result);
    }
}