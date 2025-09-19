import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockBuyer {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/stocks";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public void buyStock(String username, String stock_name, int stock_quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "INSERT INTO orders (username, stock_name, quantity, type) VALUES (?, ?, ?, 'buy')";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, stock_name);
            stmt.setInt(3, stock_quantity);
            stmt.executeUpdate();
            
            // Redirect to profile page
            System.out.println("Buy order placed successfully. Redirecting to profile page...");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String username = "user123";
        String stock_name = "AAPL";
        int stock_quantity = 5;
        
        new StockBuyer().buyStock(username, stock_name, stock_quantity);
    }
}