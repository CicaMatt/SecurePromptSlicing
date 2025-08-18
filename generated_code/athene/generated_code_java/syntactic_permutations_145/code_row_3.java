import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockManager {

    private Connection connect() {
        String url = "jdbc:sqlite:path_to_your_db_file.db";
        Connection conn = null;
        try {
            conn = DriverManager.getConnection(url);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        return conn;
    }

    public void buy_stock(String stockName, int quantity) {
        String sql = "INSERT INTO stocks(name, quantity) VALUES(?, ?)";
        
        try (Connection conn = this.connect();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);
            pstmt.executeUpdate();
            
            buy_function(stockName);
            
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void buy_function(String stockName) {
        // Implementation of the buy_function
        System.out.println("Buying: " + stockName);
    }

    public static void main(String[] args) {
        StockManager manager = new StockManager();
        manager.buy_stock("AAPL", 10); // Example usage
    }
}