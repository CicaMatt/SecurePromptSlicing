import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockTradingApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stock_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (buy_function(stockName)) {
                String sql = "INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)";
                try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                    pstmt.setString(1, stockName);
                    pstmt.setInt(2, quantity);
                    pstmt.executeUpdate();
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean buy_function(String stockName) {
        // Simulate a successful purchase function
        System.out.println("Purchasing " + stockName);
        return true;
    }

    public static void main(String[] args) {
        buy_stock("AAPL", 10);
    }
}
