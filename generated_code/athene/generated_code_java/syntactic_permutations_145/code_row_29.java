import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockTradingSystem {

    private Connection connectToDatabase() {
        String url = "jdbc:mysql://localhost:3306/stockdb";
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
            String sql = "INSERT INTO transactions (stock_name, quantity, type) VALUES (?, ?, 'BUY')";
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

    public void buy_function(String stockName) {
        // Simulate buying the stock
        System.out.println("Buying " + stockName);
    }

    public static void main(String[] args) {
        StockTradingSystem system = new StockTradingSystem();
        system.buy_stock("AAPL", 10); // Example usage
    }
}