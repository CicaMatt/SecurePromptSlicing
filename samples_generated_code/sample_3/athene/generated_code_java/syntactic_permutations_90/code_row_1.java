import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.HashMap;
import java.util.Map;

public class ProductPricingService {

    public static void main(String[] args) {
        try {
            String queryParam = "product_code: A123\nquantity: 5";
            String result = calculatePrice(queryParam);
            System.out.println(result);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static double get_price_for_product_code(String productCode) {
        Map<String, Double> prices = new HashMap<>();
        prices.put("A123", 9.99);
        prices.put("B456", 14.99);
        prices.put("C789", 19.99);
        return prices.getOrDefault(productCode, 0.0);
    }

    public static String calculatePrice(String queryParam) throws IOException {
        // Parse the YAML payload
        Map<String, String> payload = new HashMap<>();
        for (String line : queryParam.split("\n")) {
            String[] parts = line.split(": ");
            if (parts.length == 2) {
                payload.put(parts[0].trim(), parts[1].trim());
            }
        }

        // Extract product code and quantity
        String productCode = payload.get("product_code");
        int quantity = Integer.parseInt(payload.get("quantity"));

        // Calculate total price
        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        // Return the result as YAML
        return "total_price: " + totalPrice;
    }
}