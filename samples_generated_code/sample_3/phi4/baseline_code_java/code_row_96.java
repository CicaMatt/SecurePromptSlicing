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

        Connection connection = null;
        PreparedStatement preparedStatement = null;

        try {
            // Establish a connection
            connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database_name", 
                "your_username", 
                "your_password"
            );

            // Prepare SQL statement to insert buy order into the database
            String sql = "INSERT INTO BuyOrders (username, stock_name, quantity) VALUES (?, ?, ?)";
            preparedStatement = connection.prepareStatement(sql);
            
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, stockName);
            preparedStatement.setInt(3, stockQuantity);

            // Execute the insert operation
            preparedStatement.executeUpdate();

            System.out.println("Buy order inserted successfully.");

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        // Redirect to profile page (simulated by printing message)
        System.out.println("Redirecting to the profile page...");
    }
}