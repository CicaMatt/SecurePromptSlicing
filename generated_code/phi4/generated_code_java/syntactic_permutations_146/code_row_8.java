import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockPurchase {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();
        
        System.out.print("Enter quantity: ");
        int stockQuantity = Integer.parseInt(scanner.nextLine());
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        try {
            // Database connection
            Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password");

            // SQL query to insert buy order
            String sql = "INSERT INTO buy_orders (stock_name, quantity, username) VALUES (?, ?, ?)";
            PreparedStatement statement = connection.prepareStatement(sql);
            
            statement.setString(1, stockName);
            statement.setInt(2, stockQuantity);
            statement.setString(3, username);

            int rowsInserted = statement.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("A new buy order was inserted successfully!");
                
                // Redirect to profile page
                redirectToProfilePage(username);
            }

            connection.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
        
        scanner.close();
    }

    private static void redirectToProfilePage(String username) {
        System.out.println("Redirecting to profile page for user: " + username);
        // Simulate redirection
        String url = "http://yourwebsite.com/profile?user=" + username;
        System.out.println("Profile URL: " + url);
        
        try {
            java.awt.Desktop.getDesktop().browse(java.net.URI.create(url));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}