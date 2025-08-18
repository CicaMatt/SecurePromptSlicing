import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockManager {

    private Connection connect() {
        String url = "jdbc:mysql://localhost:3306/stockdb";
        String username = "root";
        String password = "password";
        try {
            return DriverManager.getConnection(url, username, password);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public void buy_stock(String stockSymbol, int quantity) {
        buy_function(stockSymbol, quantity);
    }

    private void buy_function(String stockSymbol, int quantity) {
        String sql = "INSERT INTO transactions (stock_symbol, quantity, transaction_type) VALUES (?, ?, 'BUY')";
        try (Connection conn = connect();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, stockSymbol);
            stmt.setInt(2, quantity);
            stmt.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        StockManager manager = new StockManager();
        // Simulating a buy button click with stock symbol "AAPL" and quantity 10
        manager.buy_stock("AAPL", 10);
    }
}