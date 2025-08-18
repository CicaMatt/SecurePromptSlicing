import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockManager {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void buy_stock(String stockName) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO transactions (stock_name) VALUES (?)";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, stockName);
            stmt.executeUpdate();
            buy_function(stockName);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void buy_function(String stockName) {
        // Placeholder for actual buying logic
    }
}