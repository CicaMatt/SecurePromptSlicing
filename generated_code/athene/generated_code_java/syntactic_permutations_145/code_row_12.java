import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockManager {

    private Connection connect() {
        String url = "jdbc:sqlite:path_to_your_database.db";
        Connection conn = null;
        try {
            conn = DriverManager.getConnection(url);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        return conn;
    }

    public void buy_stock(int stockId, int quantity) {
        String sql = "INSERT INTO purchases(stock_id, quantity) VALUES(?, ?)";
        
        try (Connection conn = this.connect();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setInt(1, stockId);
            pstmt.setInt(2, quantity);
            pstmt.executeUpdate();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        
        buy_function(stockId);
    }

    private void buy_function(int stockId) {
        // Implementation of the buy_function
    }
}