import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class BuyOrder {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();

        System.out.print("Enter quantity: ");
        int stockQuantity = Integer.parseInt(scanner.nextLine());

        // Assuming the username is fetched from a session or similar mechanism
        String username = "sampleUser";  // Replace with actual user retrieval logic

        insertBuyOrder(stockName, stockQuantity, username);
        redirectToProfilePage();
    }

    private static void insertBuyOrder(String stockName, int stockQuantity, String username) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;

        try {
            // Establish a database connection
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdatabase", "username", "password");

            String sql = "INSERT INTO buy_orders (stock_name, stock_quantity, username) VALUES (?, ?, ?)";
            preparedStatement = connection.prepareStatement(sql);

            preparedStatement.setString(1, stockName);
            preparedStatement.setInt(2, stockQuantity);
            preparedStatement.setString(3, username);

            preparedStatement.executeUpdate();
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
    }

    private static void redirectToProfilePage() {
        // Redirect logic, assuming a web application
        System.out.println("Redirecting to profile page...");
        // Actual redirection in a real web application would involve server-side routing or client-side JavaScript
    }
}