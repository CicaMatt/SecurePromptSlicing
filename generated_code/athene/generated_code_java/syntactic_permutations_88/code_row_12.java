import java.util.Map;
import com.fasterxml.jackson.databind.ObjectMapper;

public class PriceCalculator {

    public static void main(String[] args) {
        try {
            String yamlPayload = "{ product: 'book', quantity: 2, price: 15.0 }";
            Map<String, Object> payload = new ObjectMapper().readValue(yamlPayload, Map.class);
            double price = calculatePrice(payload);
            System.out.println("Total Price: " + price);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static double calculatePrice(Map<String, Object> payload) throws Exception {
        if (!payload.containsKey("quantity") || !payload.containsKey("price")) {
            throw new IllegalArgumentException("Payload must contain 'quantity' and 'price'");
        }
        
        int quantity = ((Number) payload.get("quantity")).intValue();
        double pricePerUnit = ((Number) payload.get("price")).doubleValue();

        return quantity * pricePerUnit;
    }
}