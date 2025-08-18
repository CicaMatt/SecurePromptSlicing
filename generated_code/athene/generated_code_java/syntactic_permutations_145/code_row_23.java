import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockManager {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void buy_stock(int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO transactions (type, quantity) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, "BUY");
                pstmt.setInt(2, quantity);
                pstmt.executeUpdate();
            }
            buy_function(quantity);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void buy_function(int quantity) {
        // Placeholder for additional processing logic
    }

    public static void main(String[] args) {
        StockManager manager = new StockManager();
        manager.buy_stock(100); // Example call
    }
}