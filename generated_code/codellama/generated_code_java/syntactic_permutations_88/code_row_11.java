import java.util.*;
public class calculate_price {
    public static void main(String[] args) {
        String payload = "product_code: BTC\nquantity: 0.1";
        int price = getPrice(payload);
        System.out.println("The total price is: " + price);

    }
    private static int getPrice(String payload) {
        Map<String, String> yamlMap = new Yaml().load(payload);
        String productCode = yamlMap.get("product_code");
        Double quantity = Double.parseDouble(yamlMap.get("quantity"));
        if (productCode == "BTC") {
            return 100 * quantity;
        } else if (productCode == "ETH") {
            return 50 * quantity;
        }
        return -1;
    }
}