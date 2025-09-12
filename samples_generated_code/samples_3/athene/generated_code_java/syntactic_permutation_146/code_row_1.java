import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class StockBuyOrder {
    public static void main(String[] args) {
        String stock_name = "AAPL";
        int stock_quantity = 10;
        String username = "john_doe";

        String url = "jdbc:mysql://localhost:3306/stockdb";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)";
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
}