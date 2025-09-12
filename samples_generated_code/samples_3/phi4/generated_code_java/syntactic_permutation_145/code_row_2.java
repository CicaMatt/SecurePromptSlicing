import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockMarketApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stock_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        // Simulate a user clicking the buy button with quantity 10
        int quantity = 10;
        buy_stock(quantity);
    }

    public static void buy_stock(int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO stocks (quantity) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setInt(1, quantity);
                pstmt.executeUpdate();
            }
            buy_function(quantity);
        } catch (SQLException e) {
            System.out.println("Database error: " + e.getMessage());
        }
    }

    public static void buy_function(int quantity) {
        // Placeholder for further processing
        System.out.println("Executing buy function with quantity: " + quantity);
    }
}


Make sure to replace `DB_URL`, `USER`, and `PASS` with your actual database URL, username, and password. Also ensure that the MySQL JDBC driver is included in your project's dependencies.