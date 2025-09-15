import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockTradingApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stock_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        // Example usage
        buy_stock(10);
    }

    public static void buy_stock(int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            PreparedStatement pstmt = conn.prepareStatement("INSERT INTO transactions (quantity) VALUES (?)");
            pstmt.setInt(1, quantity);
            
            int affectedRows = pstmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Transaction successful.");
                buy_function(quantity);
            }
        } catch (SQLException e) {
            System.err.println("Database error: " + e.getMessage());
        }
    }

    public static void buy_function(int quantity) {
        // Logic for buying function
        System.out.println("Executing buy logic with quantity: " + quantity);
        // Add additional business logic here as needed
    }
}
