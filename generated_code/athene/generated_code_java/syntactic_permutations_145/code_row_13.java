import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockManager {

    private Connection connect() {
        String url = "jdbc:sqlite:path_to_db";
        Connection conn = null;
        try {
            conn = DriverManager.getConnection(url);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        return conn;
    }

    public void buy_stock(String stockName) {
        insertStockIntoDatabase(stockName);
        buy_function(stockName);
    }

    private void insertStockIntoDatabase(String stockName) {
        String sql = "INSERT INTO stocks(name) VALUES(?)";
        
        try (Connection conn = this.connect();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, stockName);
            pstmt.executeUpdate();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private void buy_function(String stockName) {
        // Implementation of the buy function
        System.out.println("Buying stock: " + stockName);
    }
}