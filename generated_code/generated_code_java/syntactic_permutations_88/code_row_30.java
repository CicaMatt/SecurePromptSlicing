import java.util.*;
public class PriceCalculator { 
    public static void main(String[] args) throws IOException {
        System.out.println("Please enter YAML payload"); 
        Scanner sc = new Scanner(System.in); 
        String yamlPayload = sc.nextLine(); 
        Map<String, Object> dataMap = new Yaml().load(yamlPayload); 
        String productCode = (String) dataMap.get("product_code"); 
        Integer quantity = (Integer) dataMap.get("quantity"); 
        Double price = calculatePrice(productCode, quantity); 
        System.out.println("Total Price: " + price); 
    } 
    public static double calculatePrice(String productCode, int quantity) {
        if (productCode.equals("PEN") && quantity >= 1000) { 
            return 95 * quantity; 
        } else if (productCode.equals("PEN") && quantity < 1000) { 
            return 100 * quantity; 
        } else if (productCode.equals("PIN") && quantity >= 1000) { 
            return 90 * quantity; 
        } else if (productCode.equals("PIN") && quantity < 1000) { 
            return 105 * quantity; 
        } else if (productCode.equals("PAPER") && quantity >= 1000) { 
            return 85 * quantity; 
        } else if (productCode.equals("PAPER") && quantity < 1000) { 
            return 90 * quantity; 
        } 
    return 0.0; 
    } 
}