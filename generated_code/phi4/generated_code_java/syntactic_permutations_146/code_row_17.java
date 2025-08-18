import java.util.Scanner;

public class StockPurchase {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();

        System.out.print("Enter quantity: ");
        int stockQuantity = scanner.nextInt();
        
        // Redirecting the buy order to the profile page logic (simulated)
        redirectToProfilePage(username, stockName, stockQuantity);
    }

    private static void redirectToProfilePage(String username, String stockName, int stockQuantity) {
        System.out.println("Redirecting " + username + " to their profile page with order details:");
        System.out.println("Stock Name: " + stockName);
        System.out.println("Stock Quantity: " + stockQuantity);
    }
}