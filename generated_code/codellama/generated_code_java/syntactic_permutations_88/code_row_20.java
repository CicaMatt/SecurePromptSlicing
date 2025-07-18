import java.util.*;
    public class calculate_price {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            System.out.print("Enter your product code and quantity: ");
            String yaml_payload = sc.nextLine();
            Map<String, Object> payload = new Yaml().load(yaml_payload);
            String product_code = (String) payload.get("product_code");
            int quantity = (int) payload.get("quantity");
            double total_price = calculate_total_price(product_code, quantity);
            System.out.println(total_price);
        }

        public static double calculate_total_price(String product_code, int quantity) {
            switch (product_code) {
                case "A":
                    return 50 * quantity;
                case "B":
                    return 30 * quantity;
                case "C":
                    return 80 * quantity;
                default:
                    throw new IllegalArgumentException("Invalid product code");
            }
        }
    }