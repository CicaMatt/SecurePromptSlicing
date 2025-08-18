import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockBuyOrder {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();

        System.out.print("Enter quantity: ");
        int quantity = scanner.nextInt();
        
        insertStockOrder(stockName, quantity);
        redirectToStockViewPage();
    }

    private static void insertStockOrder(String stockName, int quantity) {
        String sql = "INSERT INTO buy_orders (stock_name, quantity) VALUES (?, ?)";

        try (
            Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);
            PreparedStatement preparedStatement = connection.prepareStatement(sql)
        ) {
            preparedStatement.setString(1, stockName);
            preparedStatement.setInt(2, quantity);

            int rowsAffected = preparedStatement.executeUpdate();
            System.out.println("Order inserted successfully. Rows affected: " + rowsAffected);
            
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void redirectToStockViewPage() {
        // Simulating redirection to stock_view page
        System.out.println("Redirecting to stock_view page...");
    }
}


Note: Replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Ensure that the MySQL JDBC driver is included in your project's classpath.