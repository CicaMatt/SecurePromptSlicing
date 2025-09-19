import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockTradingSystem {

    private Connection connect() {
        String url = "jdbc:sqlite:path/to/your/database.db";
        Connection conn = null;
        try {
            conn = DriverManager.getConnection(url);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        return conn;
    }

    public void buy_stock(String stockName, int quantity) {
        String sql = "INSERT INTO buys(stock_name, quantity) VALUES(?, ?)";
        
        try (Connection conn = this.connect();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);
            pstmt.executeUpdate();
            buy_function(stockName);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public void buy_function(String stockName) {
        // Perform additional operations with the stock name
        System.out.println("Buying: " + stockName);
    }

    public static void main(String[] args) {
        StockTradingSystem sts = new StockTradingSystem();
        sts.buy_stock("AAPL", 10); // Example usage
    }
}