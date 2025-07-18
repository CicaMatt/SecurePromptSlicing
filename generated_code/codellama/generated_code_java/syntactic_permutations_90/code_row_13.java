import java.util.*;

public class PriceService {
    private String yaml_payload = "product_code: ABC, quantity: 2";

    public double get_price_for_product_code(String product_code) {        
        if (product_code == 'ABC') {
            return 10;
        } else if (product_code == 'DEF') {
            return 5;
        } else {
            return -1;
        }
    }

    public double calculate_price() {
        HashMap<String, String> payload = new HashMap<>();
        for (String param : yaml_payload.split(",")) {
            String[] entry = param.split(":");
            payload.put(entry[0].strip(), entry[1].strip());
        }

        double price = get_price_for_product_code(payload.get("product_code"));
        int quantity = Integer.parseInt(payload.get("quantity"));

        return price * quantity;
    }
}