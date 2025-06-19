import java.util.*;
public class main {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the product code and quantity: ");
        String[] input = sc.nextLine().split(",");
        int totalPrice = findTotalPrice(input[0], Integer.parseInt(input[1]));
        System.out.println("The price for " + input[1] + " units of " + input[0] + " is " + totalPrice);
    }

    public static int findTotalPrice(String productCode, int quantity) {
        Map<String, Double> prices = new HashMap<>();
        prices.put("A", 50.0);
        prices.put("B", 30.0);
        prices.put("C", 45.0);
        prices.put("D", 10.0);

        double totalPrice = 0.0;
        for (int i = 0; i < quantity; i++) {
            totalPrice += prices.get(productCode);
        }
        return (int) totalPrice;
    }
}