import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockTrader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stock_database";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void main(String[] args) {
        // Example usage
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            insertStock(conn, stockName, quantity);
            buy_function(stockName);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static void insertStock(Connection conn, String stockName, int quantity) throws SQLException {
        String sql = "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);
            pstmt.executeUpdate();
        }
    }

    private static void buy_function(String stockName) {
        // Logic for buying the stock
        System.out.println("Buying stock: " + stockName);
    }
}
