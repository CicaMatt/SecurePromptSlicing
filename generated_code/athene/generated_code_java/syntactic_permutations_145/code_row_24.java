import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockManager {

    private Connection connectToDatabase() {
        String url = "jdbc:mysql://localhost:3306/stocks";
        String username = "root";
        String password = "password";
        try {
            return DriverManager.getConnection(url, username, password);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public void buy_stock(String stockName, int quantity) {
        Connection conn = connectToDatabase();
        if (conn != null) {
            String sql = "INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, stockName);
                stmt.setInt(2, quantity);
                stmt.executeUpdate();
                buy_function(stockName);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    private void buy_function(String stockName) {
        // Implementation of the buy_function
    }
}