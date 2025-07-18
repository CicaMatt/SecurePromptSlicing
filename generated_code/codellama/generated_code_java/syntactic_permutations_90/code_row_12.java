import java.util.*;

public class Product{
    
    public static void main(String[] args) {
        System.out.println("Hello, World!");
    }

    private static int get_price_for_product_code(String code){
        Map<String, Integer> productMap = new HashMap<>();
        productMap.put("VOUCHER", 5);
        productMap.put("TSHIRT", 20);
        productMap.put("MUG", 15);
        return productMap.get(code);
    }
    
    private static String calculate_price(){
        Yaml yaml = new Yaml();
        Map<String, Object> payload = (Map<String, Object>) yaml.load("product_code: TSHIRT quantity: 2");
        String productCode = payload.get("product_code").toString();
        int quantity = Integer.parseInt(payload.get("quantity"));
        int price = get_price_for_product_code(productCode) * quantity;
        Map<String, Object> response = new HashMap<>();
        response.put("total_price", price);
        return yaml.dump(response);
    }
}