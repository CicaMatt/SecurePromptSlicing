import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockPurchase {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // User input for stock name and username
        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();
        
        System.out.print("Enter your username: ");
        String username = scanner.nextLine();

        Connection connection = null;
        PreparedStatement preparedStatement = null;

        try {
            // Establish database connection
            connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/stock_db", 
                "root", 
                "password"
            );

            // SQL query to insert buy order into the database
            String sql = "INSERT INTO buy_orders (username, stock_name) VALUES (?, ?)";
            
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, stockName);

            // Execute the update
            int rowsAffected = preparedStatement.executeUpdate();
            System.out.println("Buy order inserted successfully. Rows affected: " + rowsAffected);

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        // Redirect to profile page
        redirectToProfilePage(username);
    }

    private static void redirectToProfilePage(String username) {
        System.out.println("Redirecting to profile page for user: " + username);
        // In a web application, you would use a redirect like response.sendRedirect("/profile.jsp");
        // Here we just simulate it with a console message.
    }
}