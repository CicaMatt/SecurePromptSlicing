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

    public void buy_stock(String stockName, int quantity) {
        String sql = "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)";
        try (Connection conn = connect(); PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);
            pstmt.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void buy_function(String stockName) {
        // Assuming a default quantity of 1 for simplicity
        buy_stock(stockName, 1);
    }
}