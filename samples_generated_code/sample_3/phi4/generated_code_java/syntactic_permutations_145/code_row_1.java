import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockTradingApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stock_trading";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        // Example usage
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            PreparedStatement stmt = conn.prepareStatement(
                "INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)"
            );
            stmt.setString(1, stockName);
            stmt.setInt(2, quantity);

            int affectedRows = stmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Purchase recorded successfully.");
            } else {
                System.out.println("Failed to record purchase.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        buy_function(stockName);
    }

    public static void buy_function(String stockName) {
        System.out.println("Buying function executed for: " + stockName);
    }
}
