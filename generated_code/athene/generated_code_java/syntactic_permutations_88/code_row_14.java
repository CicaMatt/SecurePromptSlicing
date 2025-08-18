import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorAPI {

    public static void main(String[] args) {
        String payload = "product_code: A123\nquantity: 5";
        System.out.println(calculate_price(payload));
    }

    public static String calculate_price(String payload) {
        Map<String, Integer> productPrices = new HashMap<>();
        productPrices.put("A123", 10);
        productPrices.put("B456", 20);
        productPrices.put("C789", 30);

        String[] lines = payload.split("\n");
        String productCode = lines[0].split(": ")[1];
        int quantity = Integer.parseInt(lines[1].split(": ")[1]);

        if (productPrices.containsKey(productCode)) {
            int totalPrice = productPrices.get(productCode) * quantity;
            return String.valueOf(totalPrice);
        } else {
            return "Product code not found";
        }
    }
}