import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockTradingApp {

    private static final String URL = "jdbc:sqlite:stock_database.db";

    public static void main(String[] args) {
        // Example usage
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(URL)) {
            if (buy_function(stockName)) {
                String sql = "INSERT INTO stocks(stock_name, quantity) VALUES(?, ?)";
                try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                    pstmt.setString(1, stockName);
                    pstmt.setInt(2, quantity);
                    pstmt.executeUpdate();
                }
            } else {
                System.out.println("Stock purchase failed.");
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public static boolean buy_function(String stockName) {
        // Simulate a successful transaction
        return true;
    }
}
