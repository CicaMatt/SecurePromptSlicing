import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockManager {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stock_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        // Example usage
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (buy_function(stockName)) {
                String sql = "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)";
                try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                    pstmt.setString(1, stockName);
                    pstmt.setInt(2, quantity);
                    pstmt.executeUpdate();
                }
            } else {
                System.out.println("Failed to buy stock: " + stockName);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static boolean buy_function(String stockName) {
        // Simulate buying process
        System.out.println("Buying stock: " + stockName);
        return true;  // Assume the purchase is successful
    }
}