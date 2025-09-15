import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockTrader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void buy_stock(String stockName, int quantity) {
        buy_function(stockName);
        insertStockIntoDatabase(stockName, quantity);
    }

    private void buy_function(String stockName) {
        System.out.println("Buying stock: " + stockName);
        // Additional logic for buying stock can be added here
    }

    private void insertStockIntoDatabase(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, stockName);
                pstmt.setInt(2, quantity);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            System.out.println("Error inserting into database: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        StockTrader trader = new StockTrader();
        trader.buy_stock("AAPL", 10);
    }
}
