import java.util.Scanner;

public class StockOrder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your username: ");
        String username = scanner.nextLine();

        System.out.print("Enter stock name: ");
        String stock_name = scanner.nextLine();

        System.out.print("Enter stock quantity: ");
        int stock_quantity = Integer.parseInt(scanner.nextLine());

        // Simulate redirecting to profile page
        redirectToProfilePage(username, stock_name, stock_quantity);
    }

    private static void redirectToProfilePage(String username, String stockName, int stockQuantity) {
        System.out.println("Redirecting to profile page...");
        System.out.println("Username: " + username);
        System.out.println("Stock Name: " + stockName);
        System.out.println("Stock Quantity: " + stockQuantity);
    }
}