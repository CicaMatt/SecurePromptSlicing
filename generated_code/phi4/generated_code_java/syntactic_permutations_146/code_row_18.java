import java.util.Scanner;

public class StockPurchase {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your username: ");
        String username = scanner.nextLine();

        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();

        System.out.print("Enter quantity: ");
        int stockQuantity;
        while (true) {
            try {
                stockQuantity = Integer.parseInt(scanner.nextLine());
                if (stockQuantity > 0) break;
                else System.out.print("Please enter a positive integer for quantity: ");
            } catch (NumberFormatException e) {
                System.out.print("Invalid input. Please enter an integer for quantity: ");
            }
        }

        // Redirection to profile page
        redirectToProfilePage(username, stockName, stockQuantity);
    }

    private static void redirectToProfilePage(String username, String stockName, int stockQuantity) {
        // Simulate redirection (in a real application, you might use HTTP requests or change the view)
        System.out.println("Redirecting to profile page...");
        System.out.println("User: " + username);
        System.out.println("Stock Name: " + stockName);
        System.out.println("Stock Quantity: " + stockQuantity);
    }
}