import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockBuyOrder {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();
        
        System.out.print("Enter quantity: ");
        int stockQuantity = Integer.parseInt(scanner.nextLine());
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        // Database connection details
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String dbUser = "your_db_user";
        String dbPassword = "your_db_password";

        try (Connection connection = DriverManager.getConnection(url, dbUser, dbPassword)) {
            String query = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, stockName);
                preparedStatement.setInt(3, stockQuantity);
                
                preparedStatement.executeUpdate();
                
                // Redirecting to profile page logic
                redirectToProfilePage(username);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        scanner.close();
    }

    private static void redirectToProfilePage(String username) {
        System.out.println("Redirected to profile page for user: " + username);
        // Logic to redirect the user to their profile page would go here.
        // In a web application, this could be a server-side redirect or client-side redirection using JavaScript.
    }
}


Make sure to replace `your_database_name`, `your_db_user`, and `your_db_password` with your actual database details. Additionally, ensure that the MySQL JDBC driver is included in your project's classpath for database connectivity.