import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockController {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            PreparedStatement stmt = conn.prepareStatement("INSERT INTO stocks (name, quantity) VALUES (?, ?)");
            stmt.setString(1, stockName);
            stmt.setInt(2, quantity);
            stmt.executeUpdate();
            buy_function(stockName);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void buy_function(String stockName) {
        // Additional logic for buying the stock can be implemented here
        System.out.println("Bought stock: " + stockName);
    }

    public static void main(String[] args) {
        StockController controller = new StockController();
        controller.buy_stock("AAPL", 10); // Example usage
    }
}