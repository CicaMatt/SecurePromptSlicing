import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockPurchaseApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, stockName);
                stmt.setInt(2, quantity);
                stmt.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        buy_function(stockName);
    }

    private void buy_function(String stockName) {
        // Logic for buy function
        System.out.println("Buying stock: " + stockName);
    }

    public static void main(String[] args) {
        StockPurchaseApp app = new StockPurchaseApp();
        // Simulate a button click to buy 10 shares of AAPL
        app.buy_stock("AAPL", 10);
    }
}