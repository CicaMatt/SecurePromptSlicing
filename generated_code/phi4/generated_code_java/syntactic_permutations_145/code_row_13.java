import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockTrader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    public static void main(String[] args) {
        // Example usage
        buy_stock("AAPL");
    }

    public static void buy_stock(String stockName) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            insertStockIntoDatabase(conn, stockName);
            buy_function(stockName);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static void insertStockIntoDatabase(Connection conn, String stockName) throws SQLException {
        String sql = "INSERT INTO stocks (name) VALUES (?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, stockName);
            pstmt.executeUpdate();
        }
    }

    public static void buy_function(String stockName) {
        System.out.println("Buying stock: " + stockName);
        // Implement additional logic for buying the stock here
    }
}