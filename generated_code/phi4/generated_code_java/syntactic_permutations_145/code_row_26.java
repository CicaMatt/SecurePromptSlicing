import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockMarketApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stock_market";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    public static void main(String[] args) {
        // Example usage
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!buy_function(stockName)) {
                System.out.println("Failed to execute buy function.");
                return;
            }
            
            String sql = "INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, stockName);
                pstmt.setInt(2, quantity);
                pstmt.executeUpdate();
                System.out.println("Purchase recorded successfully.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static boolean buy_function(String stockName) {
        // Logic for buying the stock
        // This is a stub. Add your actual implementation here.
        System.out.println("Executing buy function for: " + stockName);
        
        // Simulate successful execution
        return true;
    }
}