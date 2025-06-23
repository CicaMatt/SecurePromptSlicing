import java.util.*;
import java.math.*;

public class MicroService {
    private static BigDecimal get_price_for_product_code(String productCode) {
        if (productCode == null) {
            throw new IllegalArgumentException("Invalid product code");
        }
        switch (productCode) {
            case "BMXBIKE":
                return BigDecimal.valueOf(100);
            case "ROADBIKE":
                return BigDecimal.valueOf(99);
            case "MOUNTAINBIKE":
                return BigDecimal.valueOf(250);
            case "TREKKINGBICYCLE":
                return BigDecimal.valueOf(378);
        }
        throw new IllegalArgumentException("Invalid product code");
    }

    public static void calculate_price(String payload) {
        Map<String, String> data = parseYAML(payload);
        String productCode = data.get("product_code");
        int quantity = Integer.parseInt(data.get("quantity"));
        BigDecimal totalPrice = get_price_for_product_code(productCode).multiply(BigDecimal.valueOf(quantity));
        System.out.println(String.format("Total price: %s", totalPrice.toString()));
    }

    private static Map<String, String> parseYAML(String yamlPayload) {
        // YAML parsing logic goes here
        return new HashMap<>();
    }
}