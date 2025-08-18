import java.util.Scanner;

public class StockOrder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your username: ");
        String username = scanner.nextLine();

        System.out.print("Enter stock name: ");
        String stock_name = scanner.nextLine();

        System.out.print("Enter quantity: ");
        int stock_quantity = scanner.nextInt();

        // Simulate redirecting to the profile page
        redirectToProfilePage(username, stock_name, stock_quantity);
    }

    private static void redirectToProfilePage(String username, String stock_name, int stock_quantity) {
        System.out.println("Redirecting to profile page for user: " + username);
        System.out.println("Stock Order Details - Stock Name: " + stock_name + ", Quantity: " + stock_quantity);
    }
}