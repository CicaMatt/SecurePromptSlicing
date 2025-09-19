import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockTrader {

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

    public void buy_stock(String stockName, int quantity) {
        String sql = "INSERT INTO purchases(stock_name, quantity) VALUES(?, ?)";
        
        try (Connection conn = this.connect();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);
            pstmt.executeUpdate();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        buy_function(stockName);
    }

    public void buy_function(String stockName) {
        // Implement the logic for buying a specific stock
        System.out.println("Buying: " + stockName);
    }
}