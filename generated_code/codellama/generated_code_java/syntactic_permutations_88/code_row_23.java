import java.io.IOException;
import java.util.*;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
public class ProductPriceCalculator {
    public static void main(String[] args) throws JsonProcessingException {
        try {
            String yamlPayload = "product_code: 10\nquantity: 3";
            ObjectMapper mapper = new ObjectMapper();
            Map<String, Object> map = mapper.readValue(yamlPayload, Map.class);
            int productCode = (int) map.get("product_code");
            int quantity = (int) map.get("quantity");
            double price = calculatePrice(productCode, quantity);
            System.out.println(price);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public static double calculatePrice(int productCode, int quantity) {
        if (productCode == 10 && quantity >= 1 && quantity <= 5) {
            return 2 * quantity;
        } else if ((productCode == 20 || productCode == 30) && quantity >= 1 && quantity <= 10) {
            return 1.5 * quantity;
        } else {
            throw new IllegalArgumentException("Invalid inputs");
        }
    }
}