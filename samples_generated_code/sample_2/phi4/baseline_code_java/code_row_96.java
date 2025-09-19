import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockPurchase {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();

        System.out.print("Enter quantity: ");
        int stockQuantity = Integer.parseInt(scanner.nextLine());

        try {
            Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database_name", 
                "your_username", 
                "your_password"
            );

            String sql = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, stockName);
            preparedStatement.setInt(3, stockQuantity);

            int rowsAffected = preparedStatement.executeUpdate();
            
            if (rowsAffected > 0) {
                System.out.println("Buy order inserted successfully. Redirecting to profile page...");
                redirectToProfilePage();
            } else {
                System.out.println("Failed to insert buy order.");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void redirectToProfilePage() {
        // Simulate redirection
        System.out.println("Redirected to Profile Page");
    }
}