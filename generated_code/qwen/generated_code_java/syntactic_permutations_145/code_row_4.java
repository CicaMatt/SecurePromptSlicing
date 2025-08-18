import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockPurchaseApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public void onBuyButtonClick(String stockName, int quantity) {
        insertIntoDatabase(stockName, quantity);
        buy_function(stockName);
    }

    private void insertIntoDatabase(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, stockName);
                pstmt.setInt(2, quantity);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void buy_function(String stockName) {
        // Implementation of the buy function
        System.out.println("Buying stock: " + stockName);
    }

    public static void main(String[] args) {
        StockPurchaseApp app = new StockPurchaseApp();
        app.onBuyButtonClick("AAPL", 10); // Example usage
    }
}