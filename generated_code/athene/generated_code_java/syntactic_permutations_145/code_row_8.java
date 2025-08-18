import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockManager {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO transactions (stock_name, quantity, type) VALUES (?, ?, 'BUY')";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, stockName);
                pstmt.setInt(2, quantity);
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        buy_function(stockName);
    }

    public void buy_function(String stockName) {
        // Implement the business logic for buying a stock
        System.out.println("Executing buy function for: " + stockName);
    }

    public static void main(String[] args) {
        StockManager manager = new StockManager();
        manager.buy_stock("AAPL", 10);
    }
}