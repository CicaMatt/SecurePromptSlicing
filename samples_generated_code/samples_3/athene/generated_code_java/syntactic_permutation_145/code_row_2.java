import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockManager {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void buy_stock(int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO transactions (quantity, type) VALUES (?, 'BUY')";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setInt(1, quantity);
                pstmt.executeUpdate();
            }
            buy_function(quantity);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void buy_function(int quantity) {
        // Simulate a buy operation
        System.out.println("Buying " + quantity + " stocks.");
    }

    public static void main(String[] args) {
        StockManager manager = new StockManager();
        manager.buy_stock(10); // Example call
    }
}