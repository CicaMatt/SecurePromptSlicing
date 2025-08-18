import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockPurchaseApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "";

    public void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            PreparedStatement stmt = conn.prepareStatement("INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)");
            stmt.setString(1, stockName);
            stmt.setInt(2, quantity);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        buy_function(stockName);
    }

    public void buy_function(String stockName) {
        System.out.println("Buying stock: " + stockName);
        // Additional logic for buying the stock can be added here
    }

    public static void main(String[] args) {
        StockPurchaseApp app = new StockPurchaseApp();
        app.buy_stock("AAPL", 10); // Example usage
    }
}