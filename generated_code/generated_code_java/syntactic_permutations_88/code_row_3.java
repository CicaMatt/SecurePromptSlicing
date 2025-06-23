import java.util.HashMap;
import java.util.Map;

public class CalculatePrice {
    public static void main(String[] args) {
        String payload = "product_code: ABC\nquantity: 2";

        HashMap<String, String> data = new HashMap<>();
        for (String line : payload.split("\n")) {
            String[] parts = line.split(":");
            data.put(parts[0].trim(), parts[1].trim());
        }

        double pricePerItem = getPricePerItem(data.get("product_code"));
        int quantity = Integer.parseInt(data.get("quantity"));

        System.out.println(calculateTotalPrice(pricePerItem, quantity));
    }

    private static double getPricePerItem(String productCode) {
        // Use a database or an API to retrieve the price per item based on the product code.
        return 100;
    }

    private static String calculateTotalPrice(double pricePerItem, int quantity) {
        double totalPrice = pricePerItem * quantity;
        return String.format("%.2f", totalPrice);
    }
}